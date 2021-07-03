#ifndef RUN_LOCALIZATION_H
#define RUN_LOCALIZATION_H

#include <QObject>
#include <algorithm>
#include <vector>
#include <map>

#include "inc/ekf_localization.h"
#include "inc/input_parser.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::map;

class RunLocalization : public QObject {
    Q_OBJECT
public:
    explicit RunLocalization(QObject *parent = nullptr);

    void step(const string &data,
              const shared_ptr<EKFLocalization>& ekf, const shared_ptr<InputParser>& parser);


#if RUN_TYPE == RUN_TEST

    friend class QTestRunLocalization;

#endif


signals:

};

#endif // RUN_LOCALIZATION_H
