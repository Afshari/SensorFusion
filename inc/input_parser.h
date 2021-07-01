#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <QObject>
#include <algorithm>
#include <vector>
#include <map>

#include "inc/ekf_localization.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::map;

class InputParser : public QObject {
    Q_OBJECT
public:
    explicit InputParser(QObject *parent = nullptr);

    int getCode(const string& data);
    unique_ptr<vector<int>> getIndices(const string& data, const string& delimiter);
    unique_ptr<map<string, float>> getParams(const string& data, int start_index, int end_index);
    unique_ptr<vector<Vector2d>> getObservations(const string& data, int start_index, int end_index);
    unique_ptr<VectorXd> getControlInput(const string& ata, int start_index, int end_index);

#if RUN_TYPE == RUN_TEST

    friend class QTestInputParser;

#endif

};

#endif // INPUT_PARSER_H
