/*
 * BlockBlockShapeRecognize.hpp
 *
 *  Created on: 20-01-2013
 *      Author: spiatek
 */

#ifndef BLOCKSHAPERECOGNIZE_HPP_
#define BLOCKSHAPERECOGNIZE_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <map>

#include "ObjectModel.hpp"
#include "ObjectInstance.hpp"

#include "Types/SegmentedImage.hpp"

using namespace std;

namespace Processors {
namespace CspBlockObjectRecognize {

/**
 * Recognizes shapes from given objects models.
 */
class BlockShapeRecognize
{
public:
	BlockShapeRecognize();
	virtual ~BlockShapeRecognize();

	/**
	 * Set models to recognize.
	 * Every model will be checked.
	 * @param models
	 */
	void setModels(const std::map <std::string, boost::shared_ptr <ObjectModel> >& models);

	/**
	 * Recognize objects in segments.
	 * @param vs segments vector
	 * @param vn lines vector
	 * @param vls lines' segments numbers
	 * @return recognize object instances.
	 */
	ObjectInstanceVector recognizeVS(vector<Types::Segmentation::Segment>& vs, vector<cv::Vec4i>& vn, vector<int>& vls);
private:
	std::map <std::string, boost::shared_ptr <ObjectModel> > models;
};

} // namespace CspBlockObjectRecognize
} // namespace Processors

#endif /* BLOCKSHAPERECOGNIZE_HPP_ */
