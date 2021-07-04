#ifndef GMOCK_EKF_LOCALIZATION_H
#define GMOCK_EKF_LOCALIZATION_H

#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "inc/run_localization.h"
#include "inc/ekf_localization.h"
#include "inc/input_parser.h"
#include "tests/inc/gmock_input_parser.h"

//using namespace testing;

using std::unique_ptr;
using ::testing::_;
using testing::Eq;
using testing::Return;
using testing::ByMove;
using testing::AtLeast;

using Eigen::Vector2d;


class MockEKFLocalization : public EKFLocalization {

public:
    MOCK_METHOD7( setParams, void( float std_vel, float std_steer, float std_range, float std_bearing,
                                   float start_angle, float prior_cov_pos, float prior_cov_angle ) );

    MOCK_METHOD1( setLandmarks,     void( shared_ptr<vector<Vector2d>> landmarks ) );
    MOCK_METHOD1( predict,          void( const unique_ptr<VectorXd> &u ) );
    MOCK_METHOD2( update,           void( const unique_ptr<VectorXd> &z, const shared_ptr<VectorXd> &landmark ) );
    MOCK_METHOD2( setR,             void( const float std_range, const float std_bearing ) );
    MOCK_METHOD0( getLandmarks,     shared_ptr<vector<Vector2d>>( ) );

};



TEST(RunLocalization, Code100) {

    string data = "100:1,2";

    shared_ptr<MockEKFLocalization> ekf = make_shared<MockEKFLocalization>( );
    shared_ptr<MockInputParser> parser = make_shared<MockInputParser>();

    shared_ptr<vector<int>> indices = make_shared<vector<int>>( vector<int>( { 0, 4, 7, 15 } ) );
    map<string, float> r_params = { { "std_vel", 1 } };
    shared_ptr<map<string, float>> params = make_shared<map<string, float>>( r_params );

    vector<Vector2d> observations;
    observations.push_back( Vector2d( 1, 2 ) );
    observations.push_back( Vector2d( 3, 7 ) );
    observations.push_back( Vector2d( 4, 6 ) );
    shared_ptr<vector<Vector2d>> ptr_observations = make_shared<vector<Vector2d>>( observations );

    EXPECT_CALL( *parser, getCode( _ ) )
            .Times(1)
            .WillOnce( Return( 100 ) );

    EXPECT_CALL( *parser, getIndices( _, _ ) )
            .Times(1)
            .WillOnce( Return( indices ) );

    EXPECT_CALL( *parser, getLocalizationParams( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( params ) );

    EXPECT_CALL( *ekf, setParams( _, _, _, _, _, _, _ ) )
            .Times(1);

    EXPECT_CALL( *ekf, setLandmarks( _ ) )
            .Times(1);

    EXPECT_CALL( *parser, getLocalizationControlInput( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( ByMove( nullptr ) ) );

    EXPECT_CALL( *parser, getObservations( _, _, _ ) )
            .Times(2)
            .WillRepeatedly( Return( ptr_observations ) );

    EXPECT_CALL( *ekf, predict( _ ) )
            .Times(1);

    EXPECT_CALL( *ekf, getLandmarks() )
            .Times(1)
            .WillOnce( Return( ptr_observations ) );

    EXPECT_CALL( *ekf, update( _, _ ) )
            .Times(3);


    RunLocalization run_localization;
    run_localization.step( data , ekf, parser );

}



TEST(RunLocalization, Code101) {

    string data = "101:1,2";

    shared_ptr<MockEKFLocalization> ekf = make_shared<MockEKFLocalization>( );
    shared_ptr<MockInputParser> parser = make_shared<MockInputParser>();

    shared_ptr<vector<int>> indices = make_shared<vector<int>>( vector<int>( { 0, 4, 7, 15 } ) );
    map<string, float> r_params = { { "std_vel", 1 } };
    shared_ptr<map<string, float>> params = make_shared<map<string, float>>( r_params );

    vector<Vector2d> observations;
    observations.push_back( Vector2d( 1, 2 ) );
    observations.push_back( Vector2d( 3, 7 ) );
    observations.push_back( Vector2d( 4, 6 ) );
    shared_ptr<vector<Vector2d>> ptr_observations = make_shared<vector<Vector2d>>( observations );

    EXPECT_CALL( *parser, getCode( _ ) )
            .Times(1)
            .WillOnce( Return( 101 ) );

    EXPECT_CALL( *parser, getIndices( _, _ ) )
            .Times(1)
            .WillOnce( Return( indices ) );

    EXPECT_CALL( *parser, getLocalizationParams( _, _, _ ) )
            .Times(0);

    EXPECT_CALL( *ekf, setParams( _, _, _, _, _, _, _ ) )
            .Times(0);

    EXPECT_CALL( *ekf, setLandmarks( _ ) )
            .Times(0);

    EXPECT_CALL( *parser, getLocalizationControlInput( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( ByMove( nullptr ) ) );

    EXPECT_CALL( *parser, getObservations( _, _, _ ) )
            .Times(1)
            .WillRepeatedly( Return( ptr_observations ) );

    EXPECT_CALL( *ekf, predict( _ ) )
            .Times(1);

    EXPECT_CALL( *ekf, getLandmarks() )
            .Times(1)
            .WillOnce( Return( ptr_observations ) );

    EXPECT_CALL( *ekf, update( _, _ ) )
            .Times(3);


    RunLocalization run_localization;
    run_localization.step( data , ekf, parser );

}








#endif // GMOCK_EKF_LOCALIZATION_H
