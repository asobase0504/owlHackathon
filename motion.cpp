//**************************************************************************************************
//
// モーション処理(motion.cpp)
// Auther：唐?ｱ結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include <stdio.h>
#include <assert.h>
#include "manager.h"
#include "motion.h"
#include "utility.h"	

CModelManager * CModelManager::ms_ModelManager;

//=============================================================================
// コンストラクタ
// Author : 唐?ｱ結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CMotion::CMotion(char * pFileName)
{
	// パーツ名の初期化
	memset(&m_partsFile, 0, sizeof(m_partsFile));

	// モーションの初期化
	memset(&m_motion, 0, sizeof(m_motion));

	// パーツの初期化
	memset(&m_parts, 0, sizeof(m_parts));

	// パーツ数の初期化
	m_nMaxParts = 0;
	m_nType = 0;
	// モーションの読み込み
	LoodSetMotion(pFileName);
}

//=============================================================================
// デストラクタ
// Author : 唐?ｱ結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// 初期化
// Author : 唐?ｱ結斗
// 概要 : パーツ情報のXファイル読み込み
//=============================================================================
void CMotion::Init(void)
{
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{// カウントのリセット
		CntReset(nCntMotion);
	}

	for (int i = 0; i < m_nMaxParts; i++)
	{
		// 位置と向きの初期値を保存
		(m_parts + i)->posOrigin = (m_parts + i)->pos;
		(m_parts + i)->rotOrigin = (m_parts + i)->rot;

		// パーツ情報の初期化
		(m_parts + i)->mtxWorld = {};												// ワールドマトリックス
		
		CModelManager *Manager = CModelManager::GetManager();

		CModel*Data = Manager->Load(m_partsFile[(m_parts + i)->nType].aName);

		//ここにコピーしてるからよくない読み込んでからDataをそのまま使え浜田琉雅
		(m_parts + i)->pBuffer = Data->pBuffer;
		(m_parts + i)->nNumMat = Data->nNumMat;
		(m_parts + i)->pMesh = Data->pMesh;
	}
}

//=============================================================================
// パーツの設定
// Author : 唐?ｱ結斗
// 概要 : 行列を利用して、パーツの親子関係と描画設定を行う
//=============================================================================
void CMotion::SetParts(D3DXMATRIX mtxWorld, CMotion::MODELCOLLAR Type)
{

		D3DXMATRIX mtxRot;
		D3DXMATRIX mtxTrans;
		D3DMATERIAL9 matDef;
		D3DXMATERIAL *pMat;
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int i = 0; i < m_nMaxParts; i++)
	{// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&(m_parts + i)->mtxWorld);			// 行列初期化関数

		// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			(m_parts + i)->rot.y,
			(m_parts + i)->rot.x,
			(m_parts + i)->rot.z);								// 行列回転関数

		D3DXMatrixMultiply(&(m_parts + i)->mtxWorld,
			&(m_parts + i)->mtxWorld,
			&mtxRot);											// 行列掛け算関数 

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			(m_parts + i)->pos.x,
			(m_parts + i)->pos.y,
			(m_parts + i)->pos.z);								// 行列移動関数

		D3DXMatrixMultiply(&(m_parts + i)->mtxWorld,
			&(m_parts + i)->mtxWorld,
			&mtxTrans);											// 行列掛け算関数

		// 親パーツのワールドマトリックスを保持
		D3DXMATRIX mtxParent;

		if ((m_parts + i)->nIdxModelParent == -1)
		{// 親モデルのインデックス数が-1の時
		 // 新規深度値とZバッファの深度値が同じ値ならテスト成功にする
		 //pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			mtxParent = mtxWorld;
		}
		else
		{// 新規深度値とZバッファの深度値が同じ値ならテスト成功にする
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATEREQUAL);
			mtxParent = (m_parts + (m_parts + i)->nIdxModelParent)->mtxWorld;
		}

		// 自分の親マトリックスとの掛け算
		D3DXMatrixMultiply(&(m_parts + i)->mtxWorld, &(m_parts + i)->mtxWorld, &mtxParent);

		//// サイズの反映
		//D3DXMatrixScaling()

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &(m_parts + i)->mtxWorld);

		// 現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)(m_parts + i)->pBuffer->GetBufferPointer();

		DWORD ambient;
		pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);


		switch (Type)
		{
		case CMotion::LET:
			pDevice->SetRenderState(D3DRS_AMBIENT, 0xffff0000);//あか
			break;
		case CMotion::BLUE:
			pDevice->SetRenderState(D3DRS_AMBIENT, 0xff6666ff); // ほんのり青
			break;
		case CMotion::YELLOW:
			pDevice->SetRenderState(D3DRS_AMBIENT, 0x00ffff00); // ほんのり黄色
			break;
		case CMotion::GREEN:
			pDevice->SetRenderState(D3DRS_AMBIENT, 0x0000ff00); // ほんのり緑
			break;
		case CMotion::NON:
			break;
		case CMotion::MAX:
			break;
		default:
			break;
		}
		//

		for (int nCntMat = 0; nCntMat < (int)(m_parts + i)->nNumMat; nCntMat++)
		{
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// プレイヤーパーツの描画
			(m_parts + i)->pMesh->DrawSubset(nCntMat);
		}

		pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

		// 保していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	// 新規深度値とZバッファの深度値が同じ値ならテスト成功にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// モーションの再生
// Author : 唐?ｱ結斗
// 概要 : 目的の位置まで特定のフレーム数で到着する処理をパーツごとに行う
//=============================================================================
bool CMotion::PlayMotion(const int nCntMotionSet)
{
	// 変数宣言
	bool bMotion = true;

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		if (m_motion[nCntMotionSet].nCntFrame == 0)
		{// フレームカウントが0の時
			// 目的の位置と向きの算出
			(m_parts + nCntParts)->posDest = ((m_parts + nCntParts)->posOrigin + m_motion[nCntMotionSet].keySet[m_motion[nCntMotionSet].nCntKeySet].key[nCntParts].pos) - (m_parts + nCntParts)->pos;
			(m_parts + nCntParts)->rotDest = ((m_parts + nCntParts)->rotOrigin + m_motion[nCntMotionSet].keySet[m_motion[nCntMotionSet].nCntKeySet].key[nCntParts].rot) - (m_parts + nCntParts)->rot;

			// 角度の正規化
			NormalizeAngle(&(m_parts + nCntParts)->rotDest.x);
			NormalizeAngle(&(m_parts + nCntParts)->rotDest.y);
			NormalizeAngle(&(m_parts + nCntParts)->rotDest.z);
		}

		// 変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3((m_parts + nCntParts)->posDest / (float)(m_motion[nCntMotionSet].keySet[m_motion[nCntMotionSet].nCntKeySet].nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3((m_parts + nCntParts)->rotDest / (float)(m_motion[nCntMotionSet].keySet[m_motion[nCntMotionSet].nCntKeySet].nFrame));

		// 位置の加算
		(m_parts + nCntParts)->pos += addPos;

		//	向きの加算
		(m_parts + nCntParts)->rot += addRot;

		// 角度の正規化
		NormalizeAngle(&(m_parts + nCntParts)->rotDest.x);
		NormalizeAngle(&(m_parts + nCntParts)->rotDest.y);
		NormalizeAngle(&(m_parts + nCntParts)->rotDest.z);
	}

	// フレームカウントの加算
	m_motion[nCntMotionSet].nCntFrame++;

	if (m_motion[nCntMotionSet].nCntFrame >= m_motion[nCntMotionSet].keySet[m_motion[nCntMotionSet].nCntKeySet].nFrame)
	{// フレームカウントが指定のフレーム数を超えた場合
		// フレーム数の初期化
		m_motion[nCntMotionSet].nCntFrame = 0;

		// 再生中のキー番号数の加算
		m_motion[nCntMotionSet].nCntKeySet++;

		if (m_motion[nCntMotionSet].nCntKeySet >= m_motion[nCntMotionSet].nNumKey && m_motion[nCntMotionSet].bLoop)
		{// 再生中のキー数カウントがキー数の最大値を超えたとき、そのモーションがループを使用している
			// 再生中のキー数カウントを初期化
			m_motion[nCntMotionSet].nCntKeySet = 0;

		}
		else if (m_motion[nCntMotionSet].nCntKeySet >= m_motion[nCntMotionSet].nNumKey)
		{
			m_motion[nCntMotionSet].nCntKeySet = 0;
			bMotion = false;
		}
	}

	return bMotion;
}

//=============================================================================
// モーションブレンド
// Author : 唐?ｱ結斗
// 概要 : モーションとモーションのつなぎ目を調整する
//=============================================================================
bool CMotion::MotionBlend(const int nCntMotionSet)
{
	// 変数宣言
	bool bMotionBlend = true;

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		if ((m_motion + nCntMotionSet)->nCntFrame == 0)
		{// フレームカウントが0の時
		 // 目的の位置と向きの算出
			(m_parts + nCntParts)->posDest = ((m_parts + nCntParts)->posOrigin + (m_motion + nCntMotionSet)->keySet[(m_motion + nCntMotionSet)->nCntKeySet].key[nCntParts].pos) - (m_parts + nCntParts)->pos;
			(m_parts + nCntParts)->rotDest = ((m_parts + nCntParts)->rotOrigin + (m_motion + nCntMotionSet)->keySet[(m_motion + nCntMotionSet)->nCntKeySet].key[nCntParts].rot) - (m_parts + nCntParts)->rot;

			// 角度の正規化
			NormalizeAngle(&(m_parts + nCntParts)->rotDest.x);
			NormalizeAngle(&(m_parts + nCntParts)->rotDest.y);
			NormalizeAngle(&(m_parts + nCntParts)->rotDest.z);
		}

		// 変数宣言
		D3DXVECTOR3 addPos = D3DXVECTOR3((m_parts + nCntParts)->posDest / (float)(MOTION_BLEND_FRAM));
		D3DXVECTOR3 addRot = D3DXVECTOR3((m_parts + nCntParts)->rotDest / (float)(MOTION_BLEND_FRAM));

		// 位置の加算
		(m_parts + nCntParts)->pos += addPos;

		//	向きの加算
		(m_parts + nCntParts)->rot += addRot;

		// 角度の正規化
		NormalizeAngle(&(m_parts + nCntParts)->rotDest.x);
		NormalizeAngle(&(m_parts + nCntParts)->rotDest.y);
		NormalizeAngle(&(m_parts + nCntParts)->rotDest.z);
	}

	// フレームカウントの加算
	(m_motion + nCntMotionSet)->nCntFrame++;

	if ((m_motion + nCntMotionSet)->nCntFrame >= MOTION_BLEND_FRAM)
	{// フレームカウントが指定のフレーム数を超えた場合
		// フレーム数の初期化
		(m_motion + nCntMotionSet)->nCntFrame = 0;

		// 再生中のキー番号数の加算
		(m_motion + nCntMotionSet)->nCntKeySet++;

		bMotionBlend = false;
	}

	return bMotionBlend;
}

//=============================================================================
// パーツとモーションの読み込み
// Author : 唐?ｱ結斗
// 概要 : パーツとモーションの読み込み、初期化を呼び出す
//=============================================================================
void CMotion::LoodSetMotion(char * pFileName)
{
	// 変数宣言
	char aString[128] = {};			// 文字列比較用の変数
	char g_aEqual[128] = {};		// ＝読み込み用変数
	int	nCntKeySet = 0;				// KeySetカウント
	int	nCntKey = 0;				// Keyカウント
	int nCntFileName = 0;			// ファイル名
	int nCntParts = 0;				// パーツ数のカウント
	int nCntMotion = 0;				// モーション数のカウント

	// ファイルポインタの宣言
	FILE * pFile;

	//ファイルを開く
	pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &aString);

		while (strncmp(&aString[0], "SCRIPT", 6) != 0)
		{// 文字列が一致した場合
			aString[0] = {};
			// 文字列の読み込み
			fscanf(pFile, "%s", &aString[0]);
		}
		while (strncmp(&aString[0], "END_SCRIPT", 10) != 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strncmp(&aString[0], "#", 1) == 0)
			{// 一列読み込む
				fgets(&aString[0], sizeof(aString), pFile);
			}

			if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{// ファイル名の読み込み
				fscanf(pFile, "%s", &g_aEqual[0]);
				fscanf(pFile, "%s", &m_partsFile[nCntFileName].aName[0]);

				nCntFileName++;
			}

			if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{// キャラクターの読み込み
				while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strncmp(&aString[0], "#", 1) == 0)
					{// 一列読み込む
						fgets(&aString[0], sizeof(aString), pFile);
					}

					if (strcmp(&aString[0], "NUM_PARTS") == 0)
					{// 読み込むパーツ数
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &m_nMaxParts);

						// メモリの解放
						m_parts = new Parts[m_nMaxParts];
  						m_motion = new MyMotion[MAX_MOTION];
						assert(m_parts != nullptr && m_motion != nullptr);
					}

					if (strcmp(&aString[0], "PARTSSET") == 0)
					{// パーツの読み込み
						while (strcmp(&aString[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strncmp(&aString[0], "#", 1) == 0)
							{// 一列読み込む
								fgets(&aString[0], sizeof(aString), pFile);
							}

							if (strcmp(&aString[0], "INDEX") == 0)
							{// タイプの読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &m_parts[nCntParts].nType);
							}
							if (strcmp(&aString[0], "PARENT") == 0)
							{// 親の読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &m_parts[nCntParts].nIdxModelParent);
							}
							if (strcmp(&aString[0], "POS") == 0)
							{// 位置の読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &m_parts[nCntParts].pos.x);
								fscanf(pFile, "%f", &m_parts[nCntParts].pos.y);
								fscanf(pFile, "%f", &m_parts[nCntParts].pos.z);
							}
							if (strcmp(&aString[0], "ROT") == 0)
							{// 向きの読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &m_parts[nCntParts].rot.x);
								fscanf(pFile, "%f", &m_parts[nCntParts].rot.y);
								fscanf(pFile, "%f", &m_parts[nCntParts].rot.z);
							}
						}

						// パーツカウントのインクリメント
						nCntParts++;
					}
				}
			}
			if (strcmp(&aString[0], "MOTIONSET") == 0)
			{// モーションの読み込み
				while (strcmp(&aString[0], "END_MOTIONSET") != 0)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strncmp(&aString[0], "#", 1) == 0)
					{// 一列読み込む
						fgets(&aString[0], sizeof(aString), pFile);
					}

					if (strcmp(&aString[0], "LOOP") == 0)
					{// ループ有無の読み込み
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", (int*)(&m_motion[nCntMotion].bLoop));
					}
					if (strcmp(&aString[0], "NUM_KEY") == 0)
					{// キー数の読み込み
						fscanf(pFile, "%s", &g_aEqual[0]);
						fscanf(pFile, "%d", &m_motion[nCntMotion].nNumKey);
					}
					if (strcmp(&aString[0], "KEYSET") == 0)
					{// キーセットの読み込み
						while (strcmp(&aString[0], "END_KEYSET") != 0)
						{
							fscanf(pFile, "%s", &aString[0]);

							if (strncmp(&aString[0], "#", 1) == 0)
							{// 一列読み込む
								fgets(&aString[0], sizeof(aString), pFile);
							}

							if (strcmp(&aString[0], "FRAME") == 0)
							{// フレーム数の読み込み
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &m_motion[nCntMotion].keySet[nCntKeySet].nFrame);
							}
							if (strcmp(&aString[0], "KEY") == 0)
							{// キーの読み込み
								while (strcmp(&aString[0], "END_KEY") != 0)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (strncmp(&aString[0], "#", 1) == 0)
									{// 一列読み込む
										fgets(&aString[0], sizeof(aString), pFile);
									}

									if (strcmp(&aString[0], "POS") == 0)
									{// 位置の読み込み
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].pos.x);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].pos.y);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].pos.z);
									}
									if (strcmp(&aString[0], "ROT") == 0)
									{// 向きの読み込み
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].rot.x);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].rot.y);
										fscanf(pFile, "%f", &m_motion[nCntMotion].keySet[nCntKeySet].key[nCntKey].rot.z);
									}
								}

								// キーカウントのインクリメント
								nCntKey++;
							}
						}

						// キーカウントの初期化
						nCntKey = 0;

						// キーセットカウントのインクリメント
						nCntKeySet++;
					}
				}
				// キーセットカウントの初期化
				nCntKeySet = 0;

				// パーツ情報のインクリメント
				nCntMotion++;
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		assert(false);
	}

	// 初期化
	Init();
}

//=============================================================================
// 終了
// Author : 唐?ｱ結斗
// 概要 : メモリの解放
//=============================================================================
void CMotion::Uninit(void)
{
	if (m_parts != nullptr)
	{
		delete m_parts;
		m_parts = nullptr;
	}

	if (m_motion != nullptr)
	{
		delete[] m_motion;
		m_motion = nullptr;
	}
}

//=============================================================================
// カウントのリセット
// Author : 唐?ｱ結斗
// 概要 : カウントのリセット
//=============================================================================
void CMotion::CntReset(const int nNumMotionOld)
{
	m_motion[nNumMotionOld].nCntFrame = 0;
	m_motion[nNumMotionOld].nCntKeySet = 0;
}

//=============================================================================
// マネージャーのコンストラクタ
// Author :浜田琉雅
// 概要 : 数値の初期化
//=============================================================================
CModelManager::CModelManager()
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		m_apModel[i] = nullptr;
	}
}

//=============================================================================
//  マネージャーのデス
// Author : 浜田琉雅
// 概要 : 
//=============================================================================
CModelManager::~CModelManager()
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		assert(m_apModel[i] == nullptr);
	}
}

//=============================================================================
// カウントのリセット
// Author : 浜田琉雅
// 概要 : カウントのリセット
//=============================================================================
CModelManager * CModelManager::GetManager()
{
	if (ms_ModelManager == nullptr)
	{
		ms_ModelManager = new CModelManager;
	}
	return ms_ModelManager;
}

//=============================================================================
// モデルのロード
// Author : 浜田琉雅
// 概要 : モデルのロード
//=============================================================================
CModel*  CModelManager::Load(const char *pXFileName)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (m_apModel[i] == nullptr)
		{
			continue;
		}

		if (strcmp(m_apModel[i]->m_xFilename, &pXFileName[0]) == 0)
		{
			m_apModel[i]->nType = i;
			return m_apModel[i];
		}
	}

	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (m_apModel[i] == nullptr)
		{

			m_apModel[i] = new CModel;
			strcpy(m_apModel[i]->m_xFilename, &pXFileName[0]);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(pXFileName,
				D3DXMESH_SYSTEMMEM,
				CManager::GetInstance()->GetRenderer()->GetDevice(),
				NULL,
				&m_apModel[i]->pBuffer,
				NULL,
				&m_apModel[i]->nNumMat,
				&m_apModel[i]->pMesh);
			m_apModel[i]->nType = i;
			return m_apModel[i];
		}
	}

	assert(false);
	return nullptr;
}

//=============================================================================
// Xfileのよみこみ
// Author : 浜田琉雅
// 概要 : Xfileのよみこみ
//=============================================================================

CModel * CModelManager::LoadXfile(const char * pXFileName)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (m_apModel[i] == nullptr)
		{
			continue;
		}

		if (strcmp(m_apModel[i]->m_xFilename, &pXFileName[0]) == 0)
		{
			m_apModel[i]->nType = i;
			return m_apModel[i];
		}
	}

	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (m_apModel[i] == nullptr)
		{

			m_apModel[i] = new CModel;
			//strcpy(m_apModel[i]->m_xFilename, &pXFileName[0]);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(pXFileName,
				D3DXMESH_SYSTEMMEM,
				CManager::GetInstance()->GetRenderer()->GetDevice(),
				NULL,
				&m_apModel[i]->pBuffer,
				NULL,
				&m_apModel[i]->nNumMat,
				&m_apModel[i]->pMesh);
			m_apModel[i]->nType = i;
			return m_apModel[i];
		}
	}

	assert(false);
	return nullptr;
}

//=============================================================================
//  モデルの破棄
// Author : 浜田琉雅
// 概要 : モデルの破棄
//=============================================================================
void CModelManager::ReleaseAll()
{
	CModelManager *Manager = CModelManager::GetManager();
	if (Manager != nullptr)
	{
		for (int i = 0; i < MODEL_MAX; i++)
		{
			if (Manager->m_apModel[i] != nullptr)
			{
				Manager->m_apModel[i]->Uninit();
				delete Manager->m_apModel[i];
				Manager->m_apModel[i] = nullptr;
			}
		}
		if (ms_ModelManager != nullptr)
		{
			delete ms_ModelManager;
			ms_ModelManager = nullptr;
		}
	
	}
}

//=============================================================================
// モデルのコンストラクタ
// Author : 浜田琉雅
// 概要 : 数字の初期化
//=============================================================================
CModel::CModel():
	nType(-1),
	pMesh(nullptr),
	pBuffer(nullptr),
	nNumMat(0)
{
	m_xFilename[0] = '\0';
}
