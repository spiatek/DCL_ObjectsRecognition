/*
 * FindBlock2.hpp
 *
 *  Created on: 22-10-2011
 *      Author: spiatek
 */

#ifndef FINDBLOCK2_PROCESSOR_HPP_
#define FINDBLOCK2_PROCESSOR_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include "Types/SegmentedImage.hpp"
#include "Types/DrawableContainer.hpp"
#include "Types/Drawable.hpp"
#include "Types/ImagePosition.hpp"

#define	AVERAGE	1
#define	NEAREST	2

namespace Processors {
namespace FindBlock2 {

class FindBlock2Translator {
public:
	static int fromStr(const std::string & s)
	{
		if(s == "NEAREST") 		return NEAREST;
		if(s == "AVERAGE") 		return AVERAGE;
								return AVERAGE;
	}
	static std::string toStr(int t)
	{
		switch(t) {
			case NEAREST :		return "NEAREST";
			case AVERAGE :		return "AVERAGE";
			default :			return "NEAREST";
		}
	}
};

class FindBlock2_Processor: public Base::Component
{
public:
        FindBlock2_Processor(const std::string & name = "");
        virtual ~FindBlock2_Processor();
    	void prepareInterface();

protected:

        /*!
    	 * Method called when component is initialized
    	 * \return true on success
    	 */
        bool onInit();

    	/*!
    	 * Method called when component is finished
    	 * \return true on success
    	 */
        bool onFinish();

    	/*!
    	 * Method called when step is called
    	 * \return true on success
    	 */
        bool onStep();

        /*!
         * Method called when component is started
         * \return true on success
         */
        bool onStart();

    	/*!
    	 * Method called when component is stopped
    	 * \return true on success
    	 */
        bool onStop();

private:       
		void onLineSegmentsEstimated();

		/** Image stream. */
		Base::DataStreamIn <Types::Segmentation::SegmentedImage> in_lineSegmentsEstimated;

		/** Position stream. */
		Base::DataStreamOut <Types::ImagePosition> out_imagePosition;
        Base::DataStreamOut <Types::DrawableContainer> out_points;
        Base::DataStreamOut <Types::DrawableContainer> out_lines;

        /** New image event handler. */
  		Base::EventHandler2 h_onLineSegmentsEstimated;

    	//FindBlock2_Props props;
        Base::Property<int, FindBlock2Translator> type;
        Base::Property<int> len_min;
        Base::Property<int> len_max;
};
}
}

/*
 * Register processor component.
 */
REGISTER_COMPONENT("FindBlock2", Processors::FindBlock2::FindBlock2_Processor)

#endif /* FINDBLOCK2_PROCESSOR_HPP_ */
