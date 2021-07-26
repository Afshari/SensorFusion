#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

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

template<typename Type, int Size>
using Vector1d = Matrix<Type, Size, 1>;

class InputParser : public QObject {
    Q_OBJECT
public:
    explicit InputParser(QObject *parent = nullptr);

    virtual int getCode(const string& data);
    virtual shared_ptr<vector<int>> getIndices(const string& data, const string& delimiter);
    virtual shared_ptr<map<string, float>> getLocalizationParams(const string& data, int start_index, int len);
    virtual shared_ptr<map<string, float>> getTrackingParams(const string& data, int start_index, int len);
    virtual shared_ptr<vector<Vector2d>> getObservations(const string& data, int start_index, int len);
    virtual shared_ptr<vector<VectorXd>> getSuspensionObservations(const string& data, int start_index, int len);
    virtual unique_ptr<VectorXd> getLocalizationControlInput(const string& data, int start_index, int len);
    virtual unique_ptr<VectorXd> getTrackingInput(const string& data, int start_index, int len);

#if RUN_TYPE == RUN_TEST

    friend class QTestInputParser;

#endif

};


#endif // INPUT_PARSER_H
