﻿//============================
//
// ファイル設定
// Author:hamada ryuuga
//
//============================

#include "file.h"
#include "letter.h"
#include "particle.h"
#include "manager.h"
#include "texture.h"
#include "particle_manager.h"
#include "game.h"
#include "tutorial.h"

static int index = 0;
namespace nl = nlohmann;

nl::json Effect;//リストの生成

//============================
// 全部出力（置くだけ）
//============================
void OutputStatus()
{
	/*DataEffect = GetImguiParticle();

	auto jobj = Effect.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = "data/FILE/DataEffectOutput.json";
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();*/
}

void LoadJson(const char* cUrl)
{
	std::ifstream ifs(cUrl);

	if (ifs)
	{
		CParticleManager::BundledData loadData = {};
		CParticle::Info& particleInfo = loadData.particleData;

		//StringToWString(UTF8toSjis(j["name"]));
		//DataSet.unionsname = StringToWString(UTF8toSjis(j["unions"] ["name"]));
		ifs >> Effect;

		particleInfo.maxPopPos = D3DXVECTOR3(Effect["POSMAX"]["X"], Effect["POSMAX"]["Y"], Effect["POSMAX"]["Z"]);
		particleInfo.minPopPos = D3DXVECTOR3(Effect["POSMIN"]["X"], Effect["POSMIN"]["Y"], Effect["POSMIN"]["Z"]);
		//こっちで構造体にデータを入れてます//文字は変換つけないとばぐるぞ＾＾これ-＞UTF8toSjis()
		particleInfo.move = D3DXVECTOR3(Effect["MOVE"]["X"], Effect["MOVE"]["Y"], Effect["MOVE"]["Z"]);
		particleInfo.rot = D3DXVECTOR3(Effect["ROT"]["X"], Effect["ROT"]["Y"], Effect["ROT"]["Z"]);
		particleInfo.moveTransition = D3DXVECTOR3(Effect["MOVETRANSITION"]["X"], Effect["MOVETRANSITION"]["Y"], Effect["MOVETRANSITION"]["Z"]);;

		particleInfo.color.colBigin = D3DXCOLOR(Effect["COL"]["R"], Effect["COL"]["G"], Effect["COL"]["B"], Effect["COL"]["A"]);
		particleInfo.color.colRandamMax = D3DXCOLOR(Effect["COLRANDAMMAX"]["R"], Effect["COLRANDAMMAX"]["G"], Effect["COLRANDAMMAX"]["B"], Effect["COLRANDAMMAX"]["A"]);
		particleInfo.color.colRandamMin = D3DXCOLOR(Effect["COLRANDAMMIN"]["R"], Effect["COLRANDAMMIN"]["G"], Effect["COLRANDAMMIN"]["B"], Effect["COLRANDAMMIN"]["A"]);
		particleInfo.color.colTransition = D3DXCOLOR(Effect["COLTRANSITION"]["R"], Effect["COLTRANSITION"]["G"], Effect["COLTRANSITION"]["B"], Effect["COLTRANSITION"]["A"]);
		particleInfo.color.destCol = D3DXCOLOR(Effect["DESTCOL"]["R"], Effect["DESTCOL"]["G"], Effect["DESTCOL"]["B"], Effect["DESTCOL"]["A"]);
		particleInfo.color.nEndTime = Effect["ENDTIME"];
		particleInfo.color.nCntTransitionTime = Effect["CNTTRANSITIONTIME"];
		particleInfo.color.bColTransition = Effect["BCOLTRANSITION"];
		particleInfo.color.bColRandom = Effect["COLRANDOM"];
		particleInfo.color.bRandomTransitionTime = Effect["RANDOMTRANSITIONTIME"];

		particleInfo.type = Effect["TYPE"];
		particleInfo.fWidth = Effect["WIDTH"];
		particleInfo.fHeight = Effect["HEIGHT"];
		particleInfo.fRadius = Effect["RADIUS"];
		particleInfo.fAngle = Effect["ANGLE"];
		particleInfo.fWeight = Effect["WEIGHT"];
		particleInfo.nLife = Effect["LIFE"];
		particleInfo.fAttenuation = Effect["ATTENUATION"];
		particleInfo.fWeightTransition = Effect["WEIGHTTRANSITION"];
		particleInfo.nLife = Effect["LIFE"];
		particleInfo.bBackrot = Effect["BACKROT"];
		particleInfo.fScale = Effect["SCALE"];

		static bool chack = true;

		if (chack)
		{
			if (index >= 4)
			{
				index = 0;
			}
			switch (*CManager::GetInstance()->GetMode())
			{
			case CManager::MODE_TITLE:
			
				break;
			case CManager::MODE_GAME:
				CGame::GetParticleManager()->SetBundledData(loadData, index);			
				break;
			case CManager::MODE_RESULT:
			
				break;
			case CManager::MODE_RANKING:
				break;
			case CManager::MODE_TUTORIAL:
				CTutorial::GetParticleManager()->SetBundledData(loadData, index);
				break;
			default:
				break;
			}
			index++;
		}
		else
		{
			CGame::GetParticleManager()->ChangeBundledData(0, loadData);
		}
	}

}

