#include "node_comparator.h"

bool node_comparator::operator()(const node *lhs, const node *rhs) const {
    return lhs->get_weight() > rhs->get_weight();
}