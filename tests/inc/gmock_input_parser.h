#ifndef GMOCK_INPUT_PARSER_H
#define GMOCK_INPUT_PARSER_H

#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "inc/run_tracking.h"
#include "inc/kf_tracking.h"
#include "inc/input_parser.h"


using std::unique_ptr;
using ::testing::_;
using testing::Eq;
using testing::Return;
using testing::ByMove;
using testing::AtLeast;

using Eigen::Vector2d;


class MockInputParser : public InputParser {

public:

    MOCK_METHOD1( getCode,                          int( const string& data ) );
    MOCK_METHOD2( getIndices,                       shared_ptr<vector<int>>( const string& data, const string& delimiter ) );
    MOCK_METHOD3( getLocalizationParams,            shared_ptr<map<string, float>>( const string& data, int start_index, int len ) );
    MOCK_METHOD3( getLocalizationControlInput,      unique_ptr<VectorXd>( const string& data, int start_index, int end_index ) );
    MOCK_METHOD3( getObservations,                  shared_ptr<vector<Vector2d>>( const string& data, int start_index, int len) );

    MOCK_METHOD3( getTrackingParams,                shared_ptr<map<string, float>> (const string& data, int start_index, int len) );
    MOCK_METHOD3( getTrackingInput,                 unique_ptr<VectorXd> (const string& data, int start_index, int len) );
};




#endif // GMOCK_INPUT_PARSER_H
