/*
 * CspBlocksPreprocessor.cpp
 *
 *  Created on: 16-01-2013
 *      Author: spiatek
 */

#include <memory>
#include <string>

#include "CspBlocksPreprocessor.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace CspBlocksPreprocessor {

using namespace cv;
using namespace std;
using namespace Types;

CspBlocksPreprocessor_Processor::CspBlocksPreprocessor_Processor(const std::string & name) :
	Base::Component(name)
{
	LOG(LTRACE) << "Hello CspBlocksPreprocessor_Processor\n";
}

CspBlocksPreprocessor_Processor::~CspBlocksPreprocessor_Processor()
{
	LOG(LTRACE) << "Good bye CspBlocksPreprocessor_Processor\n";
}

bool CspBlocksPreprocessor_Processor::onInit()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::initialize\n";

	// Register data streams, events and event handlers HERE!
	registerStream("in_blueSegments", &in_blueSegments);
	registerStream("in_redSegments", &in_redSegments);
	registerStream("in_greenSegments", &in_greenSegments);
	registerStream("in_yellowSegments", &in_yellowSegments);
	registerStream("in_linesVector", &in_linesVector);
	//registerStream("out_contours", &out_contours);

	h_onLineBlueSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineBlueSegmentsEstimated);
	h_onLineRedSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineRedSegmentsEstimated);
	h_onLineGreenSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineGreenSegmentsEstimated);
	h_onLineYellowSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineYellowSegmentsEstimated);
	h_onLinesEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLinesEstimated);

	registerHandler("onLineBlueSegmentsEstimated", &h_onLineBlueSegmentsEstimated);
	registerHandler("onLineRedSegmentsEstimated", &h_onLineRedSegmentsEstimated);
	registerHandler("onLineGreenSegmentsEstimated", &h_onLineGreenSegmentsEstimated);
	registerHandler("onLineYellowSegmentsEstimated", &h_onLineYellowSegmentsEstimated);

	cspBlocksReady = registerEvent("cspBlocksReady");

	return true;
}

bool CspBlocksPreprocessor_Processor::onFinish()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::finish\n";

	return true;
}

bool CspBlocksPreprocessor_Processor::onStep()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::step\n";
	return true;
}

bool CspBlocksPreprocessor_Processor::onStop()
{
	return true;
}

bool CspBlocksPreprocessor_Processor::onStart()
{
	return true;
}

void CspBlocksPreprocessor_Processor::onLineBlueSegmentsEstimated()
{
	Types::Segmentation::SegmentedImage blue_si = in_blueSegments.read();
}

void CspBlocksPreprocessor_Processor::onLineRedSegmentsEstimated()
{
	Types::Segmentation::SegmentedImage red_si = in_redSegments.read();
}

void CspBlocksPreprocessor_Processor::onLineGreenSegmentsEstimated()
{
	Types::Segmentation::SegmentedImage green_si = in_greenSegments.read();
}

void CspBlocksPreprocessor_Processor::onLineYellowSegmentsEstimated()
{
	Types::Segmentation::SegmentedImage yellow_si = in_yellowSegments.read();
}

void CspBlocksPreprocessor_Processor::onLinesEstimated()
{
	DrawableContainer dc;

	cv::Vec4i lines = in_linesVector.read();

	cspBlocksReady->raise();
}

}//: namespace CspBlocksPreprocessor
}//: namespace Processors
