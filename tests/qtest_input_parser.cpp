#include "inc/qtest_input_parser.h"

QTestInputParser::QTestInputParser(QObject *parent) : QObject(parent) {

}

void QTestInputParser::testGetCode() {

    InputParser inputParser;

    int code = inputParser.getCode("100:12,20");
    QVERIFY(code == 100);

    code = inputParser.getCode("12,20");
    QVERIFY(code == -1);

    code = inputParser.getCode("25");
    QVERIFY(code == -1);
}



void QTestInputParser::testGetIndices() {

    InputParser inputParser;

    string data = "100:3.5292, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.858,-0.564;18.400,-0.565;18.693,-0.524;19.246,-0.561;18.227,0.705;19.060,0.657;19.922,0.628;20.770,0.614;20.300,0.524;18.239,-3.715;18.832,-3.734;19.450,-3.796;20.093,-3.795;14.659,-2.417;15.402,-2.448;16.201,-2.497;17.012,-2.524:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<vector<int>> indices = inputParser.getIndices( data, ":" );
    vector<int> ref_indices = { 0, 4, 45, 278 };
    QVERIFY( equal(indices->begin(), indices->end(), ref_indices.begin()) );


    data = "101:4.3896, -0.0001:17.614,-0.451;18.173,-0.552;18.468,-0.439;18.993,-0.522;18.494,0.672;19.300,0.614;20.143,0.656;21.006,0.559;20.493,0.558;18.495,-3.701;19.097,-3.795;19.732,-3.777;20.381,-3.823;14.351,-2.431;15.145,-2.389;15.954,-2.512;16.778,-2.558";
    indices = inputParser.getIndices( data, ":" );
    ref_indices = { 0, 4, 20 };
    QVERIFY( equal(indices->begin(), indices->end(), ref_indices.begin()) );


    data = "101:13.1687, -0.0000:15.634,-0.247;15.939,-0.259;16.604,-0.171;16.888,-0.274;21.669,0.810;22.386,0.831;23.113,0.777;23.853,0.788;23.219,0.700;21.667,-3.943;22.416,-3.977;23.173,-3.934;23.927,-4.008;11.847,-2.705;12.777,-2.717;13.740,-2.809;14.689,-2.744";
    indices = inputParser.getIndices( data, ":" );
    ref_indices = { 0, 4, 21 };
    QVERIFY( equal(indices->begin(), indices->end(), ref_indices.begin()) );
}

void QTestInputParser::testGetLocalizationControlInput() {

    InputParser inputParser;

    string data = "100:3.5292, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.858,-0.564;18.400,-0.565;18.693,-0.524;19.246,-0.561;18.227,0.705;19.060,0.657;19.922,0.628;20.770,0.614;20.300,0.524;18.239,-3.715;18.832,-3.734;19.450,-3.796;20.093,-3.795;14.659,-2.417;15.402,-2.448;16.201,-2.497;17.012,-2.524:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<vector<int>> indices = inputParser.getIndices( data, ":" );
    int start_index = (*indices)[1];
    int len = (*indices)[2] - (*indices)[1] - 1;
    unique_ptr<VectorXd> controlInput = inputParser.getLocalizationControlInput(data, start_index, len);
    float r = (*controlInput)[0];
    float theta = (*controlInput)[1];
    QVERIFY( fabs( r - 3.5292 ) < 1e-4 );
    QVERIFY( fabs( theta - 0.0001 ) < 1e-4 );


    data = "101:4.3896, -0.0001:17.614,-0.451;18.173,-0.552;18.468,-0.439;18.993,-0.522;18.494,0.672;19.300,0.614;20.143,0.656;21.006,0.559;20.493,0.558;18.495,-3.701;19.097,-3.795;19.732,-3.777;20.381,-3.823;14.351,-2.431;15.145,-2.389;15.954,-2.512;16.778,-2.558";
    indices = inputParser.getIndices( data, ":" );
    start_index = (*indices)[1];
    len = (*indices)[2] - (*indices)[1] - 1;
    controlInput = inputParser.getLocalizationControlInput(data, start_index, len);
    r = (*controlInput)[0];
    theta = (*controlInput)[1];
    QVERIFY( fabs( r - 4.3896 ) < 1e-4 );
    QVERIFY( fabs( theta - (-0.0001) ) < 1e-4 );


    data = "101:13.1687, -0.0000:15.634,-0.247;15.939,-0.259;16.604,-0.171;16.888,-0.274;21.669,0.810;22.386,0.831;23.113,0.777;23.853,0.788;23.219,0.700;21.667,-3.943;22.416,-3.977;23.173,-3.934;23.927,-4.008;11.847,-2.705;12.777,-2.717;13.740,-2.809;14.689,-2.744";
    indices = inputParser.getIndices( data, ":" );
    start_index = (*indices)[1];
    len = (*indices)[2] - (*indices)[1] - 1;
    controlInput = inputParser.getLocalizationControlInput(data, start_index, len);
    r = (*controlInput)[0];
    theta = (*controlInput)[1];
    QVERIFY( fabs( r - 13.1687 ) < 1e-4 );
    QVERIFY( fabs( theta - (-0.0000) ) < 1e-4 );
}


void QTestInputParser::testGetLocalizationParams() {

    InputParser inputParser;

    string data = "100:3.5292, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.858,-0.564;18.400,-0.565;18.693,-0.524;19.246,-0.561;18.227,0.705;19.060,0.657;19.922,0.628;20.770,0.614;20.300,0.524;18.239,-3.715;18.832,-3.734;19.450,-3.796;20.093,-3.795;14.659,-2.417;15.402,-2.448;16.201,-2.497;17.012,-2.524:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<vector<int>> indices = inputParser.getIndices( data, ":" );

    unique_ptr<EKFLocalization> ekf = make_unique<EKFLocalization>( 0.1, 0.5, 0.1, 0.1 );

    int start_index = (*indices)[1];
    int len = (*indices)[2] - (*indices)[1] - 1;
    shared_ptr<map<string, float>> params = inputParser.getLocalizationParams(data, start_index, len);

    ekf->setParams( (*params)["std_vel"], (*params)["std_steer"], (*params)["std_range"],
            (*params)["std_bearing"], (*params)["start_angle"], (*params)["prior_cov_pos"],
            (*params)["prior_cov_angle"]);

    QVERIFY( fabs( ekf->t - 0.1 ) < 1e-4 );
    QVERIFY( fabs( ekf->w - 0.5 ) < 1e-4 );
    QVERIFY( fabs( ekf->std_vel - 0.1 ) < 1e-4 );
    QVERIFY( fabs( ekf->std_steer - (1 * M_PI / 180) ) < 1e-4 );

    QVERIFY( fabs( (*ekf->R)(0, 0) - pow(0.3, 2) ) < 1e-4 );
    QVERIFY( fabs( (*ekf->R)(1, 1) - pow(0.1, 2) ) < 1e-4 );

    QVERIFY( fabs( (*ekf->x)(0) - 0 ) < 1e-4 );
    QVERIFY( fabs( (*ekf->x)(1) - 0 ) < 1e-4 );
    QVERIFY( fabs( (*ekf->x)(2) - 1.5 ) < 1e-4 );

    QVERIFY( fabs( (*ekf->P)(0, 0) - 0.1 ) < 1e-4 );
    QVERIFY( fabs( (*ekf->P)(1, 1) - 0.1 ) < 1e-4 );
    QVERIFY( fabs( (*ekf->P)(2, 2) - 0.1 ) < 1e-4 );
}


void QTestInputParser::testGetTrackingParams() {

    InputParser inputParser;

    string data = "100:95,75:0,0,0.1,0.1,0.1,1";
    shared_ptr<vector<int>> indices = inputParser.getIndices( data, ":" );

    int start_index = (*indices)[2];
    int len         = (*indices)[3] - (*indices)[2] - 1;
    shared_ptr<map<string, float>> params = inputParser.getTrackingParams(data, start_index, len);

    QVERIFY( fabs( (*params)["init_x"]  - 0   )     < 1e-4 );
    QVERIFY( fabs( (*params)["init_y"]  - 0   )     < 1e-4 );
    QVERIFY( fabs( (*params)["std_x"]   - 0.1 )     < 1e-4 );
    QVERIFY( fabs( (*params)["std_y"]   - 0.1 )     < 1e-4 );
    QVERIFY( fabs( (*params)["dt"]      - 0.1 )     < 1e-4 );
    QVERIFY( fabs( (*params)["process_noise"] - 1 ) < 1e-4 );
}


void QTestInputParser::testGetLandmarks() {

    InputParser inputParser;

    string data = "100:3.5292, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.858,-0.564;18.400,-0.565;18.693,-0.524;19.246,-0.561;18.227,0.705;19.060,0.657;19.922,0.628;20.770,0.614;20.300,0.524;18.239,-3.715;18.832,-3.734;19.450,-3.796;20.093,-3.795;14.659,-2.417;15.402,-2.448;16.201,-2.497;17.012,-2.524:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<vector<int>> indices = inputParser.getIndices( data, ":" );

    unique_ptr<EKFLocalization> ekf = make_unique<EKFLocalization>( 0.1, 0.5, 0.1, 0.1 );

    int start_index = (*indices)[3];
    int len = data.length() - (*indices)[3];
    shared_ptr<vector<Vector2d>> landmarks = inputParser.getObservations(data, start_index, len);
    ekf->setLandmarks( landmarks );

    vector<Vector2d> ref_landmarks;
    ref_landmarks.push_back( Vector2d(  10, 15 ) );
    ref_landmarks.push_back( Vector2d(  11, 15 ) );
    ref_landmarks.push_back( Vector2d(  10, 16 ) );
    ref_landmarks.push_back( Vector2d(  11, 16 ) );
    ref_landmarks.push_back( Vector2d( -10, 15 ) );
    ref_landmarks.push_back( Vector2d( -10, 16 ) );
    ref_landmarks.push_back( Vector2d( -10, 17 ) );
    ref_landmarks.push_back( Vector2d( -10, 18 ) );
    ref_landmarks.push_back( Vector2d( -9,  18 ) );
    ref_landmarks.push_back( Vector2d( -10, -15 ) );
    ref_landmarks.push_back( Vector2d( -11, -15 ) );
    ref_landmarks.push_back( Vector2d( -12, -15 ) );
    ref_landmarks.push_back( Vector2d( -13, -15 ) );
    ref_landmarks.push_back( Vector2d(  10, -11 ) );
    ref_landmarks.push_back( Vector2d(  10, -12 ) );
    ref_landmarks.push_back( Vector2d(  10, -13 ) );
    ref_landmarks.push_back( Vector2d(  10, -14 ) );

    QVERIFY(ekf->landmarks->size() == ref_landmarks.size());

    for(auto i = 0U; i < ref_landmarks.size(); i++) {
        QVERIFY(ekf->landmarks->at(i)(0) == ref_landmarks.at(i)(0) &&
                ekf->landmarks->at(i)(1) == ref_landmarks.at(i)(1));
    }
}


void QTestInputParser::testGetObservations() {

    InputParser inputParser;

    string data = "100:3.5292, 0.0001,0.1,1,0.3,0.1,1.5,0.1,0.1:17.858,-0.564;18.400,-0.565;18.693,-0.524;19.246,-0.561;18.227,0.705;19.060,0.657;19.922,0.628;20.770,0.614;20.300,0.524;18.239,-3.715;18.832,-3.734;19.450,-3.796;20.093,-3.795;14.659,-2.417;15.402,-2.448;16.201,-2.497;17.012,-2.524:10,15;11,15;10,16;11,16;-10,15;-10,16;-10,17;-10,18;-9,18;-10,-15;-11,-15;-12,-15;-13,-15;10,-11;10,-12;10,-13;10,-14";
    shared_ptr<vector<int>> indices = inputParser.getIndices( data, ":" );

    int start_index = (*indices)[2];
    int len = (*indices)[3] - (*indices)[2] - 1;

    shared_ptr<vector<Vector2d>> observations = inputParser.getObservations(data, start_index, len);

    vector<Vector2d> ref_observations;
    ref_observations.push_back( Vector2d( 17.858 , -0.564 ) );
    ref_observations.push_back( Vector2d( 18.4 , -0.565 ) );
    ref_observations.push_back( Vector2d( 18.693 , -0.524 ) );
    ref_observations.push_back( Vector2d( 19.246 , -0.561 ) );
    ref_observations.push_back( Vector2d( 18.227 , 0.705 ) );
    ref_observations.push_back( Vector2d( 19.06 , 0.657 ) );
    ref_observations.push_back( Vector2d( 19.922 , 0.628 ) );
    ref_observations.push_back( Vector2d( 20.77 , 0.614 ) );
    ref_observations.push_back( Vector2d( 20.3 , 0.524 ) );
    ref_observations.push_back( Vector2d( 18.239 , -3.715 ) );
    ref_observations.push_back( Vector2d( 18.832 , -3.734 ) );
    ref_observations.push_back( Vector2d( 19.45 , -3.796 ) );
    ref_observations.push_back( Vector2d( 20.093 , -3.795 ) );
    ref_observations.push_back( Vector2d( 14.659 , -2.417 ) );
    ref_observations.push_back( Vector2d( 15.402 , -2.448 ) );
    ref_observations.push_back( Vector2d( 16.201 , -2.497 ) );
    ref_observations.push_back( Vector2d( 17.012 , -2.524 ) );


    QVERIFY(observations->size() == ref_observations.size());

    for(auto i = 0U; i < ref_observations.size(); i++) {
        QVERIFY( fabs( observations->at(i)(0) - ref_observations.at(i)(0)  ) < 1e-4 &&
                 fabs( observations->at(i)(1) - ref_observations.at(i)(1)  ) < 1e-4 );
    }
}

