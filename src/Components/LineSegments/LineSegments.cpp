/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include <boost/bind.hpp>

#include "LineSegments.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace LineSegments {

using Types::Segmentation::SegmentedImage;
using namespace Types;

LineSegments_Processor::LineSegments_Processor(const std::string & name) :
	Base::Component(name)
{
	LOG(LTRACE) << "Hello LineSegments_Processor\n";
}

LineSegments_Processor::~LineSegments_Processor()
{
	LOG(LTRACE) << "Good bye LineSegments_Processor\n";
}

void LineSegments_Processor::prepareInterface()
{
	LOG(LTRACE) << "LineSegments_Processor::prepareInterface\n";

	// Register data streams, events and event handlers HERE!

	registerStream("in_edgesDetected", &in_edgesDetected);
	registerStream("out_lineSegmentsEstimated", &out_lineSegmentsEstimated);
	registerStream("out_lineSegments", &out_lineSegments);

	h_onEdgesDetected.setup(boost::bind(&LineSegments_Processor::onEdgesDetected, this));
	registerHandler("onEdgesDetected", &h_onEdgesDetected);

	addDependency("onEdgesDetected", &in_edgesDetected);

	//lineSegmentsEstimated = registerEvent("lineSegmentsEstimated");
}

bool LineSegments_Processor::onInit()
{
	LOG(LTRACE) << "LineSegments_Processor::initialize\n";

	return true;
}

bool LineSegments_Processor::onFinish()
{
	LOG(LTRACE) << "LineSegments_Processor::finish\n";

	return true;
}

bool LineSegments_Processor::onStep()
{
	LOG(LTRACE) << "LineSegments_Processor::step\n";
	return true;
}

bool LineSegments_Processor::onStop()
{
	return true;
}

bool LineSegments_Processor::onStart()
{
	return true;
}

void LineSegments_Processor::onEdgesDetected()
{
	LOG(LTRACE) << "LineSegments_Processor::onEdgesDetected()\n";
	SegmentedImage si = in_edgesDetected.read();

	DrawableContainer dc;
	for (size_t i = 0; i < si.segments.size(); ++i) {
		LOG(LTRACE) << "LineSegments_Processor::onEdgesDetected()::process_next_segment\n";
		std::vector <Types::Line>* lines = si.segments[i].getLineSegments();
		for (size_t j = 0; j < lines->size(); ++j) {
			Line* line = new Line((*lines)[j]);
			dc.add(line);
			LOG(LTRACE) << "LineSegments_Processor::onEdgesDetected(): adding line segment\n";
		}
	}

	LOG(LTRACE) << "LineSegments_Processor::onEdgesDetected()::beforeFillStructures\n";

	out_lineSegmentsEstimated.write(si);
	out_lineSegments.write(dc);
	//lineSegmentsEstimated->raise();
}

}//: namespace LineSegments
}//: namespace Processors
