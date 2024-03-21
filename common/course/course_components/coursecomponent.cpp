#include "coursecomponent.h"

CourseComponent::CourseComponent(QObject *parent)
    : QObject{parent}
{}

int32_t CourseComponent::getOrder() const
{
    return order;
}
