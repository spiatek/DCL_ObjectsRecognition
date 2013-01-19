/*
 * CspBlocksPreprocessor.hpp
 *
 *  Created on: 16-01-2013
 *      Author: spiatek
 */

#ifndef CSPBLOCKSPREPROCESSOR_PROCESSOR_HPP_
#define CSPBLOCKSPREPROCESSOR_PROCESSOR_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Props.hpp"

#include "Types/DrawableContainer.hpp"
#include "Types/Contour.hpp"
#include "Types/SegmentedImage.hpp"

namespace Processors {
namespace CspBlocksPreprocessor {

/*
 * class CspBlocksPreprocessor_Processor
 */
class CspBlocksPreprocessor_Processor: public Base::Component
{
public:
	/*
	 * Constructor.
	 */
	CspBlocksPreprocessor_Processor(const std::string & name = "");

	/*
	 * Destructor
	 */
	virtual ~CspBlocksPreprocessor_Processor();

protected:

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
	 * Process segmented image.
	 */
	void onLineBlueSegmentsEstimated();
	void onLineRedSegmentsEstimated();
	void onLineGreenSegmentsEstimated();
	void onLineYellowSegmentsEstimated();
	void onLinesEstimated();

	/**
	 * Segmented image data stream.
	 */
	Base::DataStreamIn <Types::Segmentation::SegmentedImage> in_blueSegments;
	Base::DataStreamIn <Types::Segmentation::SegmentedImage> in_redSegments;
	Base::DataStreamIn <Types::Segmentation::SegmentedImage> in_greenSegments;
	Base::DataStreamIn <Types::Segmentation::SegmentedImage> in_yellowSegments;
	Base::DataStreamIn < vector<cv::Vec4i> > in_linesVector;

	/**
	 * Event handler for segmented image.
	 */
	Base::EventHandler <CspBlocksPreprocessor_Processor> h_onLineBlueSegmentsEstimated;
	Base::EventHandler <CspBlocksPreprocessor_Processor> h_onLineRedSegmentsEstimated;
	Base::EventHandler <CspBlocksPreprocessor_Processor> h_onLineGreenSegmentsEstimated;
	Base::EventHandler <CspBlocksPreprocessor_Processor> h_onLineYellowSegmentsEstimated;
	Base::EventHandler <CspBlocksPreprocessor_Processor> h_onLinesEstimated;

	/**
	 * Segmented image with detected edges.
	 */
	//Base::DataStreamOut <Types::Segmentation::SegmentedImage> out_edgesDetected;

	/**
	 * Detected contours.
	 */
	Base::DataStreamOut <Types::DrawableContainer> out_contours;

	Base::DataStreamOut <std::vector<Types::Segmentation::Segment> > out_segments;
	Base::DataStreamOut <std::vector<cv::Vec4i> > out_lines;
	Base::DataStreamOut <std::vector<int> > out_nearestSegments;

	Types::Segmentation::SegmentedImage blue_si;		bool isBlue;
	Types::Segmentation::SegmentedImage red_si;			bool isRed;
	Types::Segmentation::SegmentedImage green_si;		bool isGreen;
	Types::Segmentation::SegmentedImage yellow_si;		bool isYellow;

	vector<cv::Vec4i> lines;							bool isLines;
		bool lock;										bool isReady;
		/**
	 * Edges detected event.
	 */
	Base::Event* cspBlocksReady;
};

}//: namespace CspBlocksPreprocessor
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("CspBlocksPreprocessor", Processors::CspBlocksPreprocessor::CspBlocksPreprocessor_Processor, Common::Panel_Empty)

#endif /* CSPBLOCKSPREPROCESSOR_PROCESSOR_HPP_ */
