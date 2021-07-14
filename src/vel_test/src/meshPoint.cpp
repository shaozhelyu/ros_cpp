/*
 * @Author: your name
 * @Date: 2021-07-13 18:37:51
 * @LastEditTime: 2021-07-14 12:58:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /vel_test/src/meshPoint.cpp
 */
#include <vel_test/meshPoint.h>
#include <float.h>
#include <algorithm>

meshPoint::meshPoint(std::vector<std::vector<double>> polygon):
x_ld(DBL_MAX),
y_ld(DBL_MAX),
x_ru(DBL_MIN),
y_ru(DBL_MIN)
{
    int len = polygon.size();
    for(int i=0; i<len; i++){
        x_ld = std::min(x_ld,polygon[i][0]);
        y_ld = std::min(y_ld,polygon[i][1]);
        x_ru = std::max(x_ru,polygon[i][0]);
        y_ru = std::max(y_ru,polygon[i][1]);
    }
    int row = (x_ru - x_ld)/0.3;
    int col = (y_ru - y_ld)/0.3;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            std::vector<double> tempTra;
            tempTra.push_back(0.3*i);
            tempTra.push_back(0.3*j);
            mesh.push_back(tempTra);
        }
    }
    
}