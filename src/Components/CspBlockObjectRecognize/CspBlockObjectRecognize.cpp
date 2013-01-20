/*
 * CspBlockObjectRecognize.cpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#include <memory>
#include <string>

#include "CspBlockObjectRecognize.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace CspBlockObjectRecognize {

using Types::DrawableContainer;

CspBlockObjectRecognize_Processor::CspBlockObjectRecognize_Processor(const std::string & name) :
	Base::Component(name), modelsFilename("modelsFilename")
{
	LOG(LTRACE) << "Hello CspBlockObjectRecognize_Processor\n";
	shapeRecognize = boost::shared_ptr <BlockShapeRecognize>(new BlockShapeRecognize);
	modelsFactory = boost::shared_ptr <ModelsFactory>(new ModelsFactory);

	registerProperty(modelsFilename);
}

CspBlockObjectRecognize_Processor::~CspBlockObjectRecognize_Processor()
{
	LOG(LTRACE) << "Good bye CspBlockObjectRecognize_Processor\n";
}

bool CspBlockObjectRecognize_Processor::onInit()
{
	LOG(LTRACE) << "CspBlockObjectRecognize_Processor::initialize\n";

	// Register data streams, events and event handlers HERE!
	registerStream("in_segments", &in_segments);
	registerStream("in_lines", &in_lines);
	registerStream("in_nearestSegments", &in_nearestSegments);

	h_onNewImage.setup(this, &CspBlockObjectRecognize_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("out_recognizedDrawableContainer", &out_recognizedDrawableContainer);
	recognized = registerEvent("recognized");

	//read models database
	try {
		//wczytanie zestawu modelów
		modelsFactory->setModelsFilename(modelsFilename);
		shapeRecognize->setModels(modelsFactory->loadModels());
	} catch (exception& e) {
		LOG(LFATAL) << "Error loading models from " << string(modelsFilename) << ": " << e.what() << "\n";
		return false;
	}

	return true;
}

bool CspBlockObjectRecognize_Processor::onFinish()
{
	LOG(LTRACE) << "CspBlockObjectRecognize_Processor::finish\n";

	return true;
}

bool CspBlockObjectRecognize_Processor::onStep()
{
	LOG(LTRACE) << "CspBlockObjectRecognize_Processor::step\n";
	return true;
}

bool CspBlockObjectRecognize_Processor::onStop()
{
	return true;
}

bool CspBlockObjectRecognize_Processor::onStart()
{
	return true;
}

void CspBlockObjectRecognize_Processor::onNewImage()
{
	try {
		LOG(LTRACE) << "CspBlockObjectRecognize_Processor::onNewImage()\n";

		if (in_segments.empty()) {
			LOG(LWARNING) << "CspBlockObjectRecognize_Processor::onNewImage(): buffer empty.\n";
			return;
		}

		if (in_lines.empty()) {
			LOG(LWARNING) << "CspBlockObjectRecognize_Processor::onNewImage(): buffer empty.\n";
			return;
		}

		if (in_nearestSegments.empty()) {
			LOG(LWARNING) << "CspBlockObjectRecognize_Processor::onNewImage(): buffer empty.\n";
			return;
		}

		std::vector<Types::Segmentation::Segment> vs = in_segments.read();
		std::vector<cv::Vec4i> vl = in_lines.read();
		std::vector<int> vns = in_nearestSegments.read();

		//znalezienie pasujących segmentów
		ObjectInstanceVector instances = shapeRecognize->recognizeVS(vs, vl, vns);

		DrawableContainer dc;
		BOOST_FOREACH(boost::shared_ptr<ObjectInstance> inst, instances){
			dc.add(inst->clone());
		}
		out_recognizedDrawableContainer.write(dc);
		recognized->raise();

	} catch (exception& e) {
		LOG(LFATAL) << "CspBlockObjectRecognize_Processor::onNewImage(): exception: " << e.what();
	} catch (const char * e) {
		LOG(LFATAL) << "CspBlockObjectRecognize_Processor::onNewImage(): WTF exception: " << e;
	}

}

}//: namespace CspBlockObjectRecognize
}//: namespace Processors
