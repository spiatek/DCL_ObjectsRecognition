/*
 * BlockBlockShapeRecognize.cpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#include "BlockShapeRecognize.hpp"

#include <boost/foreach.hpp>

#include "Types/Segment.hpp"
#include "LineSegment.hpp"

#include "Logger.hpp"
#include <string>
#include <iostream>

namespace Processors {
namespace CspBlockObjectRecognize {

using Types::Segmentation::Segment;

BlockShapeRecognize::BlockShapeRecognize()
{
}

BlockShapeRecognize::~BlockShapeRecognize()
{
}

void BlockShapeRecognize::setModels(const std::map <std::string, boost::shared_ptr <ObjectModel> >& models)
{
	this->models = models;
}

ObjectInstanceVector BlockShapeRecognize::recognizeVS(vector<Types::Segmentation::Segment>& vs, vector<cv::Vec4i>& vn, vector<int>& vls)
{
	ObjectInstanceVector instances;

	for(int i = 0; i < vs.size(); i++)
	{
		ShapeSegments segments;
		Segment s = vs[i];
		int color = s.getSegmentColor();

		for(int j = 0; j < vls.size(); j++)
		{
			cv::Vec4i v4l = vn[j];
			if(vls[j] == i) {
				cv::Point* p1 = new cv::Point(v4l[0], v4l[1]);
				cv::Point* p2 = new cv::Point(v4l[2], v4l[3]);
				Types::Line* line = new Types::Line(*p1, *p2);
				line->setColor(color);

				boost::shared_ptr <AbstractShape> shape = boost::shared_ptr <AbstractShape>(new LineSegment(*line));
				segments.push_back(shape);
			}
		}

		LOG(LDEBUG) << "BlockShapeRecognize::recognize(): trying to recognize segment: segments.size() = " << segments.size();

		BOOST_FOREACH(ModelsMap::value_type m, models )
		{
			std::string modelName = m.first;
			boost::shared_ptr <ObjectModel> objectModel = m.second;
			if (objectModel->findInstances(&segments)) {
				ShapeVector shapeVector = objectModel->getFoundObject();
				boost::shared_ptr<ObjectInstance> inst = boost::shared_ptr<ObjectInstance>(new ObjectInstance(objectModel, shapeVector));
				instances.push_back(inst);
				//LOG(LINFO) << "BlockShapeRecognize::recognize(): instance of " + modelName
				//		+ " found: shapeVector.size() = " << shapeVector.size();
				std::cout << "BlockShapeRecognize::recognize(): instance of " + modelName
									+ " found: shapeVector.size() = " << shapeVector.size() << std::endl;
			}
		}
	}

	std::cout << "BlockShapeRecognize::recognize(): found " << instances.size() << " instances.\n";
	return instances;
}

} // namespace CspBlockObjectRecognize
} // namespace Processors
