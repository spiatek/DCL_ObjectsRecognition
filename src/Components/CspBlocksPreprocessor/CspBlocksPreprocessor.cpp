/*
 * CspBlocksPreprocessor.cpp
 *
 *  Created on: 16-01-2013
 *      Author: spiatek
 */

#include <memory>
#include <string>
#include <time.h>

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
	registerStream("out_contours", &out_contours);

	h_onLineBlueSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineBlueSegmentsEstimated);
	h_onLineRedSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineRedSegmentsEstimated);
	h_onLineGreenSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineGreenSegmentsEstimated);
	h_onLineYellowSegmentsEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLineYellowSegmentsEstimated);
	h_onLinesEstimated.setup(this, &CspBlocksPreprocessor_Processor::onLinesEstimated);

	registerHandler("onLineBlueSegmentsEstimated", &h_onLineBlueSegmentsEstimated);
	registerHandler("onLineRedSegmentsEstimated", &h_onLineRedSegmentsEstimated);
	registerHandler("onLineGreenSegmentsEstimated", &h_onLineGreenSegmentsEstimated);
	registerHandler("onLineYellowSegmentsEstimated", &h_onLineYellowSegmentsEstimated);
	registerHandler("onLinesEstimated", &h_onLinesEstimated);

	cspBlocksReady = registerEvent("cspBlocksReady");

	isBlue = false;
	isRed = false;
	isGreen = false;
	isYellow = false;
	isLines = false;
	isReady = false;

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

	DrawableContainer dc;

	if(!isReady) {
		if(isBlue && isRed && isGreen && isYellow && isLines) {
			isReady = true;
			LOG(LTRACE) << "CspBlocksPreprocessor_Processor::bylam tu\n";
		}
		else {
			return true;
		}
	}

	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::wszystkomammogeczytac\n";

	int counter = 0;
	BOOST_FOREACH(Types::Segmentation::Segment& s, blue_si.segments) {
		std::vector <Types::Line>* lines = s.getLineSegments();
		for(size_t j = 0; j < lines->size(); ++j) {
			Line* line = new Line((*lines)[j]);
			dc.add(line);
			LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onStep(): adding line segment\n";
		}
		counter++;
	}
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::blue\n" << counter;

	counter = 0;
	BOOST_FOREACH(Types::Segmentation::Segment& s, red_si.segments) {
		std::vector <Types::Line>* lines = s.getLineSegments();
		for(size_t j = 0; j < lines->size(); ++j) {
			Line* line = new Line((*lines)[j]);
			dc.add(line);
			LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onStep(): adding line segment\n";
		}
		counter++;
	}
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::red\n" << counter;

	counter = 0;
	BOOST_FOREACH(Types::Segmentation::Segment& s, green_si.segments) {
		std::vector <Types::Line>* lines = s.getLineSegments();
		for(size_t j = 0; j < lines->size(); ++j) {
			Line* line = new Line((*lines)[j]);
			dc.add(line);
			LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onStep(): adding line segment\n";
		}
		counter++;
	}
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::green\n" << counter;

	counter = 0;
	BOOST_FOREACH(Types::Segmentation::Segment& s, yellow_si.segments) {
		std::vector <Types::Line>* lines = s.getLineSegments();
		for(size_t j = 0; j < lines->size(); ++j) {
			Line* line = new Line((*lines)[j]);
			dc.add(line);
			LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onStep(): adding line segment\n";
		}
		counter++;
	}
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::yellow\n" << counter;

	counter = 0;
	BOOST_FOREACH(cv::Vec4i & s, lines) {
		for(size_t i = 0; i < lines.size(); i++)
		{
			cv::Point* p1 = new cv::Point(s[0], s[1]);
			cv::Point* p2 = new cv::Point(s[2], s[3]);
			Types::Line* line = new Types::Line(*p1, *p2);
			dc.add(line);
		}
		counter++;
	}
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::lines\n" << counter;

	out_contours.write(dc);
	cspBlocksReady->raise();

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
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onLineBlueSegmentsEstimated\n";

	if (in_blueSegments.empty()) {
		LOG(LWARNING) << "CspBlocksPreprocessor_Processor::onLineBlueSegmentsEstimated(): buffer empty.\n";
		return;
	}

	blue_si = in_blueSegments.read();
	isBlue = true;
}

void CspBlocksPreprocessor_Processor::onLineRedSegmentsEstimated()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onLineRedSegmentsEstimated\n";

	if (in_redSegments.empty()) {
		LOG(LWARNING) << "CspBlocksPreprocessor_Processor::onLineRedSegmentsEstimated(): buffer empty.\n";
		return;
	}

	red_si = in_redSegments.read();
	isRed = true;
}

void CspBlocksPreprocessor_Processor::onLineGreenSegmentsEstimated()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onLineGreenSegmentsEstimated\n";

	if (in_greenSegments.empty()) {
		LOG(LWARNING) << "CspBlocksPreprocessor_Processor::onLineGreenSegmentsEstimated(): buffer empty.\n";
		return;
	}

	green_si = in_greenSegments.read();
	isGreen = true;
}

void CspBlocksPreprocessor_Processor::onLineYellowSegmentsEstimated()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onLineYellowSegmentsEstimated\n";

	if (in_yellowSegments.empty()) {
		LOG(LWARNING) << "CspBlocksPreprocessor_Processor::onLineYellowSegmentsEstimated(): buffer empty.\n";
		return;
	}

	yellow_si = in_yellowSegments.read();
	isYellow = true;
}

void CspBlocksPreprocessor_Processor::onLinesEstimated()
{
	LOG(LTRACE) << "CspBlocksPreprocessor_Processor::onLinesEstimated\n";
	lines = in_linesVector.read();
	isLines = true;
}

}//: namespace CspBlocksPreprocessor
}//: namespace Processors
