/*
 * CspBlockObjectRecognize.hpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#ifndef CSPBLOCKOBJECTRECOGNIZE_PROCESSOR_HPP_
#define CSPBLOCKOBJECTRECOGNIZE_PROCESSOR_HPP_

#include <boost/shared_ptr.hpp>
#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "Types/SegmentedImage.hpp"
#include "Types/DrawableContainer.hpp"
#include "BlockShapeRecognize.hpp"
#include "ModelsFactory.hpp"

#define BLUE	1
#define RED		2
#define GREEN	3
#define YELLOW	4

namespace Processors {
namespace CspBlockObjectRecognize {

class CspBlockObjectRecognize_Processor: public Base::Component
{
public:
	/*
	 * Constructor.
	 */
	CspBlockObjectRecognize_Processor(const std::string & name = "");

	/*
	 * Destructor
	 */
	virtual ~CspBlockObjectRecognize_Processor();

protected:

	void prepareInterface();

	/*
	 * Connects source to given device.
	 */
	bool onInit();

	/*
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*
	 * Retrieves data from device.
	 */
	bool onStep();

	/*
	 * Start component
	 */
	bool onStart();

	/*
	 * Stop component
	 */
	bool onStop();

private:
	/**
	 * Recognize objects in image.
	 */
	void onNewImage();

	/**
	 * Input data stream.
	 */
	Base::DataStreamIn <std::vector<Types::Segmentation::Segment> > in_segments;
	Base::DataStreamIn <std::vector<cv::Vec4i> > in_lines;
	Base::DataStreamIn <std::vector<int> > in_nearestSegments;

	/**
	 * Image event handler.
	 */
	Base::EventHandler <CspBlockObjectRecognize_Processor> h_onNewImage;

	/**
	 * Recognized objects out data stream.
	 */
	Base::DataStreamOut <Types::DrawableContainer> out_recognizedDrawableContainer;

	/**
	 * Objects recognized event.
	 */
	//Base::Event* recognized;

	/**
	 * Shape recognize object.
	 * Performs CSP graph search.
	 */
	boost::shared_ptr<BlockShapeRecognize> shapeRecognize;

	/**
	 * Object for loading models database.
	 */
	boost::shared_ptr<ModelsFactory> modelsFactory;

	/**
	 * Filename of models database.
	 *
	 */
	Base::Property<std::string> modelsFilename;
};

}//: namespace CspBlockObjectRecognize
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("CspBlockObjectRecognize", Processors::CspBlockObjectRecognize::CspBlockObjectRecognize_Processor, Common::Panel_Empty)

#endif /* CSPBLOCKOBJECTRECOGNIZE_PROCESSOR_HPP_ */
