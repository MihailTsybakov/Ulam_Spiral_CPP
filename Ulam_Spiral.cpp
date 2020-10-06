#include "CImg.h"
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

bool is_prime(int number); /// O(sqrt(n))
bool is_prime(int number)
{
    if (number == 1 || number == 2 || number == 3)
    {
        return true;
    }
    for (int i = 0; i <= static_cast<int>(sqrt(number)) + 1; i++)
    {
        if ((i >= 2) && (number % i == 0))
        {
            return false;
        }
    }
    return true;
}
void change_direction(int *dir_x, int *dir_y);
void change_direction(int *dir_x, int *dir_y)
{
    if (*dir_x != 0)
    {
        if (*dir_x == 1)
        {
            *dir_x = 0;
            *dir_y = -1;
            return;
        }
        if (*dir_x == -1)
        {
            *dir_x = 0;
            *dir_y = 1;
            return;
        }
    }
    if (*dir_x == 0)
    {
        if (*dir_y == 1)
        {
            *dir_x = 1;
            *dir_y = 0;
            return ;
        }
        if (*dir_y == -1)
        {
            *dir_x = -1;
            *dir_y = 0;
            return ;
        }
    }
}

int main(void)
{
    cimg_library::CImg<int> image(12001, 12001, 1, 3);
    int start_position_x, start_position_y;
    int direction_x, direction_y;
    int scale;
    int coil_side = 1, curr_side_pos = 0, curr_coil_pos = 0, coil_finish_flag = 0;
    int numbers_count;
    int x, y;

    /// Setting spiral params:
    start_position_x = 6040;
    start_position_y = 5950;
    scale = 4;
    direction_x = -1;
    direction_y = 0;
    numbers_count = 10000000;// 10kk
    /// --- --- --- ---

    image.fill(0);
    x = start_position_x;
    y = start_position_y;

    int start_time = clock();
    for (int i = 1; i <= numbers_count; i++)
    {
        if (i == 1)
        {
            x += scale * direction_x;
            y += scale * direction_y;
            coil_side = 3;
        }
        else
        {
            if (coil_finish_flag == 1)
            {
                curr_coil_pos = 0;
                curr_side_pos = 0;
                coil_side += 2;
                coil_finish_flag = 0;
            }
            else
            {

                if (curr_coil_pos == 0)
                {
                    x += scale * direction_x;
                    y += scale * direction_y;
                    curr_coil_pos ++;
                    curr_side_pos ++;
                    change_direction(&direction_x, &direction_y);
                }
                else
                {
                    if (curr_side_pos == coil_side - 1)
                    {
                        if (curr_coil_pos == 2*coil_side + 2*(coil_side - 2))
                        {

                            coil_finish_flag = 1;
                            continue;
                        }
                        else
                        {
                            change_direction(&direction_x, &direction_y);
                            x += scale * direction_x;
                            y += scale * direction_y;
                            curr_side_pos = 1;
                            curr_coil_pos ++;
                        }
                    }
                    else
                    {
                        x += scale * direction_x;
                        y += scale * direction_y;
                        curr_coil_pos ++;
                        curr_side_pos ++;
                    }
                }
            }

        }
        if (is_prime(i) == true)
        {
            int color[3] = {255, 255, 255};
            image.draw_point(x, y, color);
        }
        if (is_prime(i) == false)
        {
            int color[3] = {37,37,63};
            image.draw_point(x,y,color);
        }
    }
    int end_time = clock();
    int seconds_taken = (end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Seconds taken: " << seconds_taken << endl;
    /// No optimization:
    /// 800k numbers: 2 sec 42mb
    /// 3kk numbers: 13 sec 295mb 10k x 10k pixels
    /// 6kk numbers: 34 sec 295mb 10k x 10k pixels
    /// 10kk numbers: 70 sec 412mb 12k x 12k pixels
    image.save("Ulam_Spiral_bmp.bmp");
    return 0;
}

