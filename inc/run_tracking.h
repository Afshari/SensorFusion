#ifndef RUNTRACKING_H
#define RUNTRACKING_H

#include <QObject>
#include <algorithm>
#include <vector>
#include <map>

#include "inc/kf_tracking.h"
#include "inc/input_parser.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::map;

class RunTracking : public QObject {
    Q_OBJECT
public:
    explicit RunTracking(QObject *parent = nullptr);
    void step(const string &data,
              const shared_ptr<KFTracking>& kf, const shared_ptr<InputParser>& parser);

signals:

};

#endif // RUNTRACKING_H
