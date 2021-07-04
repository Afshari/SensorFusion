#include "inc/input_parser.h"

InputParser::InputParser(QObject *parent) : QObject(parent) {

}


int InputParser::getCode(const string& data) {

//    string strData;
//    strData.assign( data );
    string delimiter = ":";

    size_t pos = data.find(delimiter);
    if(pos > data.length())
        return -1;

    string token = data.substr(0, pos);
    return std::stoi(token);
}


shared_ptr<vector<int>> InputParser::getIndices(const string& data, const string& delimiter) {

    vector<int> indices;

    int pos = 0;
    indices.push_back( pos );
    while(true) {
        pos = data.find(delimiter, pos);
        if(pos == -1)
            break;
        pos += 1;
        indices.push_back( pos );
    }

    return make_shared<vector<int>>( indices );
}


shared_ptr<map<string, float>> InputParser::getLocalizationParams(const string& data, int start_index, int len) {

    string token = data.substr(start_index, len);

    auto indices = getIndices(token, ",");

    float std_vel           = std::stof( token.substr( (*indices)[2], (*indices)[3] - (*indices)[2] - 1 ) );
    float std_steer         = std::stof( token.substr( (*indices)[3], (*indices)[4] - (*indices)[3] - 1 ) );
    float std_range         = std::stof( token.substr( (*indices)[4], (*indices)[5] - (*indices)[4] - 1 ) );
    float std_bearing       = std::stof( token.substr( (*indices)[5], (*indices)[6] - (*indices)[5] - 1 ) );
    float start_angle       = std::stof( token.substr( (*indices)[6], (*indices)[7] - (*indices)[6] - 1 ) );
    float prior_cov_pos     = std::stof( token.substr( (*indices)[7], (*indices)[8] - (*indices)[7] - 1 ) );
    float prior_cov_angle   = std::stof( token.substr( (*indices)[8], (*indices)[9] - (*indices)[8] - 1 ) );

    map<string, float> result = {
        { "std_vel",            std_vel },
        { "std_steer",          std_steer },
        { "std_range",          std_range },
        { "std_bearing",        std_bearing },
        { "start_angle",        start_angle },
        { "prior_cov_pos",      prior_cov_pos },
        { "prior_cov_angle",    prior_cov_angle }
    };

    return make_shared<map<string, float>>( result );
}


shared_ptr<map<string, float>> InputParser::getTrackingParams(const string& data, int start_index, int len) {

    string token = data.substr(start_index, len);

    auto indices = getIndices(token, ",");

//    std::cout << token << std::endl;
//    std::copy(indices->begin(), indices->end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << std::endl;

    float init_x        = std::stof( token.substr( (*indices)[0], (*indices)[1]  - (*indices)[0] - 1 ) );
    float init_y        = std::stof( token.substr( (*indices)[1], (*indices)[2]  - (*indices)[1] - 1 ) );
    float std_x         = std::stof( token.substr( (*indices)[2], (*indices)[3]  - (*indices)[2] - 1 ) );
    float std_y         = std::stof( token.substr( (*indices)[3], (*indices)[4]  - (*indices)[3] - 1 ) );
    float dt            = std::stof( token.substr( (*indices)[4], (*indices)[5]  - (*indices)[4] - 1 ) );
    float process_noise = std::stof( token.substr( (*indices)[5], token.length() - (*indices)[5] ) );

    map<string, float> result = {
        { "init_x",         init_x },
        { "init_y",         init_y },
        { "std_x",          std_x },
        { "std_y",          std_y },
        { "dt",             dt },
        { "process_noise",  process_noise }
    };

    return make_shared<map<string, float>>( result );
}

unique_ptr<VectorXd> InputParser::getLocalizationControlInput(const string& data, int start_index, int len) {

    string token = data.substr(start_index, len);

    auto indices = getIndices(token, ",");

    float r = std::stof( token.substr( (*indices)[0], (*indices)[1] - (*indices)[0] - 1 ) );
    float theta = std::stof( token.substr( (*indices)[1], (*indices)[2] - (*indices)[1] - 1 ) );

    return make_unique<VectorXd>( Vector2d( r, theta ) );
}

unique_ptr<VectorXd> InputParser::getTrackingInput(const string& data, int start_index, int len) {

    string token = data.substr(start_index, len);

    auto indices = getIndices(token, ",");

    float x = std::stof( token.substr( (*indices)[0], (*indices)[1] - (*indices)[0] - 1 ) );
    float y = std::stof( token.substr( (*indices)[1], (*indices)[2] - (*indices)[1] - 1 ) );

    return make_unique<VectorXd>( Vector2d( x, y ) );
}


shared_ptr<vector<Vector2d>> InputParser::getObservations(const string& data, int start_index, int len) {

    string token = data.substr(start_index, len);
    auto indices = getIndices(token, ";");

//    std::cout << token << std::endl;
//    std::copy(indices->begin(), indices->end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << std::endl;

    vector<Vector2d> observations;

    string currObservation = "";
    for(auto i = 0U; i < indices->size(); i++) {

        if(i < indices->size() - 1) {
            currObservation = token.substr( indices->at(i), indices->at(i + 1) - indices->at(i) - 1 );
        } else {
            currObservation = token.substr( indices->at(i), token.length() );
        }
        auto idx = getIndices(currObservation, ",");
        float x = std::stof( currObservation.substr( (*idx)[0], (*idx)[1] - (*idx)[0] - 1 ) );
        float y = std::stof( currObservation.substr( (*idx)[1], currObservation.length() - (*idx)[1] ) );

        observations.push_back( Vector2d( x, y ) );
    }

    return make_shared<vector<Vector2d>>( observations );
}




//int SimpleParser::getCode(const string& data) {

//    std::ignore = data;
//    return 100;
//}











