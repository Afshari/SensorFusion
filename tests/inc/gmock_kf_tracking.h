#ifndef GMOCK_KF_TRACKING_H
#define GMOCK_KF_TRACKING_H

#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "inc/run_tracking.h"
#include "inc/kf_tracking.h"
#include "inc/input_parser.h"
#include "tests/inc/gmock_input_parser.h"

using std::unique_ptr;
using ::testing::_;
using testing::Eq;
using testing::Return;
using testing::ByMove;
using testing::AtLeast;

using Eigen::Vector2d;


class MockKFTracking : public KFTracking {

public:

    MOCK_METHOD6( init,        void(  float init_x, float init_y,
                                      float std_x, float std_y,
                                      float dt, float process_noise ) );

    MOCK_METHOD0( predict,          void( ) );
    MOCK_METHOD1( update,           void( const unique_ptr<VectorXd>& z ) );
};




TEST(KFTracking, Code100) {

    string data = "100:1,2";

    shared_ptr<MockKFTracking>  kf = make_shared<MockKFTracking>( );
    shared_ptr<MockInputParser> parser = make_shared<MockInputParser>();

    shared_ptr<vector<int>> indices = make_shared<vector<int>>( vector<int>( { 0, 4, 7, 15 } ) );
    map<string, float> r_params = { { "init_x", 1 } };
    shared_ptr<map<string, float>> params = make_shared<map<string, float>>( r_params );

    EXPECT_CALL( *parser, getCode( _ ) )
            .Times(1)
            .WillOnce( Return( 100 ) );

    EXPECT_CALL( *parser, getIndices( _, _ ) )
            .Times(1)
            .WillOnce( Return( indices ) );

    EXPECT_CALL( *parser, getTrackingParams( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( params ) );

    EXPECT_CALL( *kf, init( _, _, _, _, _, _ ) )
            .Times(1);

    EXPECT_CALL( *parser, getTrackingInput( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( ByMove( nullptr ) ) );

    EXPECT_CALL( *kf, predict( ) )
            .Times(1);

    EXPECT_CALL( *kf, update( _ ) )
            .Times(1);


    RunTracking run_tracking;
    run_tracking.step(data, kf, parser);
}



TEST(KFTracking, Code101) {

    string data = "100:1,2";

    shared_ptr<MockKFTracking>  kf = make_shared<MockKFTracking>( );
    shared_ptr<MockInputParser> parser = make_shared<MockInputParser>();

    shared_ptr<vector<int>> indices = make_shared<vector<int>>( vector<int>( { 0, 4, 7, 15 } ) );
    map<string, float> r_params = { { "init_x", 1 } };
    shared_ptr<map<string, float>> params = make_shared<map<string, float>>( r_params );

    EXPECT_CALL( *parser, getCode( _ ) )
            .Times(1)
            .WillOnce( Return( 101 ) );

    EXPECT_CALL( *parser, getIndices( _, _ ) )
            .Times(1)
            .WillOnce( Return( indices ) );

    EXPECT_CALL( *parser, getTrackingParams( _, _, _ ) )
            .Times(0);

    EXPECT_CALL( *kf, init( _, _, _, _, _, _ ) )
            .Times(0);

    EXPECT_CALL( *parser, getTrackingInput( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( ByMove( nullptr ) ) );

    EXPECT_CALL( *kf, predict( ) )
            .Times(1);

    EXPECT_CALL( *kf, update( _ ) )
            .Times(1);


    RunTracking run_tracking;
    run_tracking.step(data, kf, parser);
}







#endif // GMOCK_KF_TRACKING_H
