/*
 * @Author: your name
 * @Date: 2021-07-13 18:32:37
 * @LastEditTime: 2021-07-14 12:45:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /vel_test/include/vel_test/distributePoint.h
 */
#ifndef LFI_DISTRIBUTE_POINT_H
#define LFI_DISTRIBUTE_POINT_H
#include <vector>
class meshPoint
{
public:
    meshPoint(std::vector<std::vector<double>> polygon);
    ~meshPoint();
    int size();
private:
    int size;
    std::vector<std::vector<double>> mesh;
    std::vector<std::vector<bool>> pointState;

    double x_ld;
    double y_ld;
    double x_ru;
    double y_ru;
};

#endif