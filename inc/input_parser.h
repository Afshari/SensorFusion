#ifndef _INPUT_PARSER_H
#define _INPUT_PARSER_H

#include <QObject>
#include <algorithm>
#include <vector>
#include <map>

#include "inc/ekf_localization.h"
#include "inc/kf_tracking.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::map;
using std::tuple;

template<typename Type, int Size>
using Vector1d = Matrix<Type, Size, 1>;

class InputParser : public QObject {
    Q_OBJECT
public:
    explicit InputParser(QObject *parent = nullptr);

    virtual int getCode(const string& data);
    virtual tuple<bool, string> checkInput(const string &data);
    virtual shared_ptr<vector<int>> getIndices(const string& data, const string& delimiter);

    // Localization
    virtual shared_ptr<map<string, float>> getLocalizationParams(const string& data, int start_index, int len);
    virtual shared_ptr<Vector3d> getPFLocalizationParams(const string& data, int start_index, int len);
    virtual shared_ptr<VectorXd> getLocalizationControlInput(const string& data, int start_index, int len);
    virtual shared_ptr<vector<Vector2d>> getLocalizationMeasurements(const string& data, int start_index, int len);

    // Tracking
    virtual shared_ptr<map<string, float>> getTrackingParams(const string& data, int start_index, int len);
    virtual unique_ptr<VectorXd> getTrackingInput(const string& data, int start_index, int len);

    virtual shared_ptr<vector<Vector2d>> getObservations(const string& data, int start_index, int len);
    virtual shared_ptr<vector<VectorXd>> getSuspensionObservations(const string& data, int start_index, int len);
    virtual shared_ptr<Vector3d> getVector3(const string& data, int start_index, int len);

#if RUN_TYPE == RUN_TEST

    friend class QTestInputParser;

#endif

};


#endif // _INPUT_PARSER_H
