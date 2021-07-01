#ifndef RUN_LOCALIZATION_H
#define RUN_LOCALIZATION_H

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

class RunLocalization : public QObject
{
    Q_OBJECT
public:
    explicit RunLocalization(QObject *parent = nullptr);

    int getCode(const char* data);
    unique_ptr<vector<int>> getIndices(const string& data, const string& delimiter);
    unique_ptr<map<string, float>> getParams(const string& data, int start_index, int end_index);
    unique_ptr<vector<Vector2d>> getObservations(const string& data, int start_index, int end_index);
    unique_ptr<map<string, float>> getControlInput(const string& ata, int start_index, int end_index);

#if RUN_TYPE == RUN_TEST

    friend class QTestRunLocalization;

#endif


signals:

};

#endif // RUN_LOCALIZATION_H
