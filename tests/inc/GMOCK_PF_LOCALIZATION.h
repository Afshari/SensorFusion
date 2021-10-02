#ifndef _GMOCK_PF_LOCALIZATION_H
#define _GMOCK_PF_LOCALIZATION_H

#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

#include "inc/run_localization.h"
#include "inc/pf_localization.h"
#include "inc/input_parser.h"
#include "tests/inc/gmock_input_parser.h"

using std::unique_ptr;
using ::testing::_;
using testing::Eq;
using testing::Return;
using testing::ByMove;
using testing::AtLeast;

using Eigen::Vector2d;


class MockPFLocalization : public PFLocalization {

public:
    MockPFLocalization() : PFLocalization( nullptr ) {  }
    MOCK_METHOD1( setRobotParam,            void( const shared_ptr<Vector3d> &state ) );
    MOCK_METHOD1( setRobotMeasurements,     void( shared_ptr<vector<Vector2d>> measurements ) );
    MOCK_METHOD2( robotMove,                void( float velocity, float angular_velocity ) );
    MOCK_METHOD2( setParticleMeasurements,  void( int idx, shared_ptr<vector<Vector2d>> measurements ) );
    MOCK_METHOD2( updateParticleWeight,     void( int idx, shared_ptr<vector<Vector2d>> measurements ) );
    MOCK_METHOD3( predictParticle,          void( int idx, float velocity, float angular_velocity ) );
    MOCK_METHOD0( generateParticles,        void( void ) );
    MOCK_METHOD0( resample,                 void( void ) );
    MOCK_METHOD0( numberOfParticles,        uint( void ) );
    MOCK_METHOD0( getAllStateString,        string( void ) );

};


TEST(RunPFLocalization, Code100) {

    string data = "100:1,2";

    shared_ptr<PFRobot> robot = make_shared<PFRobot>();
    shared_ptr<MockPFLocalization> pf   = make_shared<MockPFLocalization>( );
    shared_ptr<MockInputParser> parser  = make_shared<MockInputParser>();

    shared_ptr<vector<int>> indices = make_shared<vector<int>>( vector<int>( { 0, 4, 7, 15 } ) );

    shared_ptr<Vector3d> params = make_shared<Vector3d>( Vector3d( 1, 3, 5 ) );

    tuple<bool, string> chkResult(true, "");

    EXPECT_CALL( *parser, getCode( _ ) )
            .Times(1)
            .WillOnce( Return( 100 ) );

    EXPECT_CALL( *parser, checkInput( _ ) )
            .Times(1)
            .WillOnce( Return( chkResult ) );

    EXPECT_CALL( *parser, getIndices( _, _ ) )
            .Times(1)
            .WillOnce( Return( indices ) );

    EXPECT_CALL( *parser, getPFLocalizationParams( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( params ) );

    EXPECT_CALL( *pf, setRobotParam( _ ) )
            .Times(1);

    EXPECT_CALL( *pf, generateParticles( ) )
            .Times(1);


    RunLocalization run_localization;
    run_localization.step( data , pf, parser );
}


TEST(RunPFLocalization, Code101) {

    string data = "101:1,2:32,324:23,42,3";

    shared_ptr<PFRobot> robot = make_shared<PFRobot>();
    shared_ptr<MockPFLocalization> pf   = make_shared<MockPFLocalization>( );
    shared_ptr<MockInputParser> parser  = make_shared<MockInputParser>();

    shared_ptr<vector<int>> indices = make_shared<vector<int>>( vector<int>( { 0, 4, 8, 15 } ) );
    shared_ptr<vector<int>> particles_indices = make_shared<vector<int>>( vector<int>( { 0, 4, 8, 15 } ) );
    shared_ptr<Vector3d> params = make_shared<Vector3d>( Vector3d( 1, 3, 5 ) );
    tuple<bool, string> chkResult(true, data);
    shared_ptr<VectorXd> u = make_shared<VectorXd>( Vector2d( 2, 0.2 ) );

    EXPECT_CALL( *parser, getCode( _ ) )
            .Times(1)
            .WillOnce( Return( 101 ) );

    EXPECT_CALL( *parser, checkInput( _ ) )
            .Times(1)
            .WillOnce( Return( chkResult ) );

    EXPECT_CALL( *parser, getIndices( _, ":" ) )
            .Times(1)
            .WillOnce( Return( indices ) );

    EXPECT_CALL( *parser, getIndices( _, ";" ) )
            .Times(1)
            .WillOnce( Return( particles_indices ) );

    EXPECT_CALL( *parser, getLocalizationMeasurements( _, _, _ ) )
            .Times(5)
            .WillRepeatedly( Return( nullptr ) );

    EXPECT_CALL( *parser, getPFLocalizationParams( _, _, _ ) )
            .Times(0);

    EXPECT_CALL( *parser, getLocalizationControlInput( _, _, _ ) )
            .Times(1)
            .WillOnce( Return( u ) );

    EXPECT_CALL( *pf, setRobotParam( _ ) )
            .Times(0);

    EXPECT_CALL( *pf, setRobotMeasurements( _ ) )
            .Times(1);

    EXPECT_CALL( *pf, generateParticles( ) )
            .Times(0);

    EXPECT_CALL( *pf, setParticleMeasurements( _, _ ) )
            .Times(4);

    EXPECT_CALL( *pf, updateParticleWeight( _, _ ) )
            .Times(4);

    EXPECT_CALL( *pf, resample( ) )
            .Times(1);

    EXPECT_CALL( *pf, robotMove( _, _ ) )
            .Times(1);

    EXPECT_CALL( *pf, numberOfParticles( ) )
            .Times(5)
            .WillRepeatedly( Return( 4 ) );

    EXPECT_CALL( *pf, predictParticle( _, _, _ ) )
            .Times(4);


    RunLocalization run_localization;
    run_localization.step( data , pf, parser );
}


#endif // _GMOCK_PF_LOCALIZATION_H
