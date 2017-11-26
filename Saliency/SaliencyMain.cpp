#include "stdafx.h"
int main()
{

	printf("hello\n");

	CStr wkDir = "C:/Users/Administrator/Desktop/课程设计/自然场景下显著目标的提取/test/";
	//CStr wkDir = argv[1];
	CStr inDir = wkDir + "Imgs/", outDir = wkDir + "Saliency/";
	CmFile::Copy2Dir(inDir + "*.jpg", outDir);
	
	// Saliency detection method pretended in my ICCV 2013 paper http://mmcheng.net/effisalobj/.
	//CmSaliencyGC::Demo(inDir + "*.jpg", outDir); 

	// Saliency detection method presented in PAMI 2015 (CVPR 2011) paper http://mmcheng.net/salobj/.
	CmSaliencyRC::Get(inDir + "*.jpg", outDir);

	CmSalCut::Demo(inDir + "*.jpg", inDir + "*.png", outDir);	//第二个参数没啥用


	//vecS des;
	//des.push_back("GC");  des.push_back("RC");
	//CmEvaluation::Evaluate(inDir + "*.png", outDir, wkDir + "Results.m", des);
	//CmEvaluation::EvalueMask(inDir + "*.png", outDir, "RCC", wkDir + "CutRes.m");

	return 0;
}
