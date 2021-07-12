#ifndef RUN_SUSPENSION_ESTIMATION_H
#define RUN_SUSPENSION_ESTIMATION_H

#include <QObject>
#include <algorithm>
#include <vector>
#include <map>

#include "inc/kf_passive_suspension.h"
#include "inc/input_parser.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::map;

class RunSuspensionEstimator : public QObject {
    Q_OBJECT
public:
    explicit RunSuspensionEstimator(QObject *parent = nullptr);
    std::string step(const string &data,
                     const shared_ptr<KFPassiveSuspension>& estimator, const shared_ptr<InputParser>& parser);

signals:

};

#endif // RUN_SUSPENSION_ESTIMATION_H
