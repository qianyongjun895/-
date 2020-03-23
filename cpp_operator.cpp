#include "cpp_operator.h"

cpp_operator::cpp_operator()
{

}

cpp_operator::action(QImage img)
{
    //获取图片的尺寸
    int width = img.width();
    int height= img.height();

    //定义黄色图片阈值数组
    int img_yellow [width][height];
    //初始化数组
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            img_yellow [i][j] = 0;
        }
    }

    //通过img获取图片黄色图片的灰度值
    QColor oldColor;
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            oldColor = QColor(img.pixelColor(i,j));
            //获取R和G通道，获得黄色成像图片
            int yellow_average = (oldColor.red()+oldColor.green())/2;
            img_yellow [i][j] = yellow_average;
        }
    }


    //黄色图片阈值处理
    int img_threshold [width][height];
     for(int i=0;i<width;i++)
      {
          for(int j=0;j<height;j++)
           {
               if(img_yellow [i][j]<240)
               {
                    img_threshold[i][j]=0;
               }
               else {
                   img_threshold[i][j]=255;
               }
            }
        }

//----------------提取黄色图片时候，有纯白色进行干扰，这里提取B（蓝色）通道图片进行阈值，并进行对比
     //获得蓝色通道阈值图片

     int blue_threshold [width][height];
     for(int i=0;i<width;i++)
     {
         for(int j=0;j<height;j++)
         {
             oldColor = QColor(img.pixelColor(i,j));
             //获取R和G通道，获得黄色成像图片
             if(oldColor.blue()<240)
             {
                  blue_threshold[i][j]=0;
             }
             else {
                 blue_threshold[i][j]=255;
             }
         }
     }

//------黄色阈值图片和蓝色阈值图片进行比较,相同的标记点，设置为0
     for(int i=0;i<width;i++)
     {
         for(int j=0;j<height;j++)
         {
             if(blue_threshold[i][j]==img_threshold[i][j])
             {
                 img_threshold[i][j]=0;
             }
          }
      }


//---对图片的标记点进行开运算——————

     //设置开运算中使用元的尺寸
     int element_width=5;
     int element_height=5;
     //腐蚀算子
     for(int i=0;i<width;i++)
     {
         for(int j=0;j<height;j++)
         {
            if(img_threshold[i][j]==255)
            {
                for(int element_i=0;element_i<element_width;element_i++)
                {
                    for(int element_j=0;element_j<element_height;element_j++)
                    {
                        if((i-element_width/2+element_i>0)&(j-element_height/2+element_j>0))
                        {
                            if(img_threshold[i-element_width/2+element_i][j-element_height/2+element_j]==0)
                            {
                                img_threshold[i][j]=0;
                            }
                        }
                    }
                }


            }
         }
     }

     //膨胀运算
     for(int i=0;i<width;i++)
     {
         for(int j=0;j<height;j++)
         {
            if(img_threshold[i][j]==255)
            {
                for(int element_i=0;element_i<element_width;element_i++)
                {
                    for(int element_j=0;element_j<element_height;element_j++)
                    {
                        if((i-element_width/2+element_i>0)&(j-element_height/2+element_j>0))
                        {
                            if(img_threshold[i-element_width/2+element_i][j-element_height/2+element_j]==255)
                            {
                                //腐蚀算子填充
                                for(int expand_i=i-element_width/2;expand_i<i+element_width/2;expand_i++)
                                {
                                    for(int expand_j=j-element_height/2;expand_j<i+element_height/2;expand_j++)
                                    {
                                        img_threshold[expand_i][expand_j] =255;
                                    }
                                }
                            }
                        }
                    }
                }
            }
         }
     }

//--------------------计算兴趣区域的面积和数量，采用种子点生长--------
/*
 * 图片会根据检测出来种子点的次序，依次标记兴趣区域的值。获得兴趣点区域的值可以根据兴趣点标记的次序依次获得
*/
     int num_bole = 0;
     int num_bole_area [1000] ;
     for(int i=;i<1000;i++)
     {
         num_bole_area[i]=0;
     }

     for(int i=0;i<width;i++)
     {
         for(int j=0;j<height;j++)
         {
             //定义种子节点的缓冲值
             int point_buffer_x[1000];
             int point_buffer_y[1000];
             for(int i=0;i<1000;i++)
             {
                point_buffer_x[i]=0;
                point_buffer_y[i]=0;
             }
             //定义种子BUFFER的数量值
             int buffer_are=0;
              int buffer_mun=0;
            if(img_threshold[i][j]==255) //获取种子点
            {
                num_bole++; //区域标记值
                //判断种子点周围标定点的值
                if(img_threshold[i-1][j]==255)
                {
                    point_buffer_x[buffer_mun]=i-1;
                    point_buffer_y[buffer_mun]=j;
                    buffer_are++;
                    buffer_mun++;
                }
                if(img_threshold[i+1][j]==255)
                {
                    point_buffer_x[buffer_mun]=i+1;
                    point_buffer_y[buffer_mun]=j;
                    buffer_are++;
                    buffer_mun++;
                }
                if(img_threshold[i][j-1]==255)
                {
                    point_buffer_x[buffer_mun]=i;
                    point_buffer_y[buffer_mun]=j-1;
                    buffer_are++;
                    buffer_mun++;
                }
                if(img_threshold[i][j+1]==255)
                {
                    point_buffer_x[buffer_mun]=i;
                    point_buffer_y[buffer_mun]=j+1;
                    buffer_are++;
                    buffer_mun++;
                }
                 buffer_are++;
                img_threshold[i][j]=num_bole;
                if(buffer_mun>0)
                {
                    //洪水法蔓延计算
                    for(int buffer_i=0;buffer_i<buffer_are;buffer_i++)
                    {
                        if(point_buffer_x[buffer_i]!=0)
                        {
                            if(img_threshold[point_buffer_x[buffer_i]-1][point_buffer_y[buffer_i]]==255)
                            {
                                point_buffer_x[buffer_are]=point_buffer_x[buffer_i]-1;
                                point_buffer_y[buffer_are]=point_buffer_y[buffer_i];
                                buffer_mun++;
                                buffer_are++;
                            }
                            if(img_threshold[point_buffer_x[buffer_i]+1][point_buffer_y[buffer_i]]==255)
                            {
                                point_buffer_x[buffer_are]=point_buffer_x[buffer_i]+1;
                                point_buffer_y[buffer_are]=point_buffer_y[buffer_i];
                                buffer_mun++;
                                buffer_are++;
                            }
                            if(img_threshold[point_buffer_x[buffer_i]][point_buffer_y[buffer_i]-1]==255)
                            {
                                point_buffer_x[buffer_are]=point_buffer_x[buffer_i];
                                point_buffer_y[buffer_are]=point_buffer_y[buffer_i]-1;
                                buffer_mun++;
                                buffer_are++;
                            }
                            if(img_threshold[point_buffer_x[buffer_i]][point_buffer_y[buffer_i]+1]==255)
                            {
                                point_buffer_x[buffer_are]=point_buffer_x[buffer_i];
                                point_buffer_y[buffer_are]=point_buffer_y[buffer_i]+1;
                                buffer_mun++;
                                buffer_are++;
                            }
                        }
                        img_threshold[point_buffer_x[buffer_i]][point_buffer_y[buffer_i]]=num_bole;
                        point_buffer_x[buffer_i]=0;
                        point_buffer_y[buffer_i]=0;
                        buffer_mun--;
                    }
                }
            }
            num_bole_area[num_bole]=buffer_are;
            delete []point_buffer_x;
            delete []point_buffer_y;
          }
      }

//-----------根据面积值筛选出兴趣点的值和面积大小---------
/*
    获得大于区域面积大于500的联通区域的标记值,buffer_int为符合面积的连通域数量
*/
     int sign_num[100];
     int buffer_int = 0;
     for(int i=0;i<100;i++)
     {
         sign_num[i]=0;
     }
     for(int i=0;i<1000;i++)
     {
         if(num_bole_area[i]>500)
         {
            sign_num[buffer_int]=i;
            buffer_int++;
         }
     }

//----------------获取有效连通域的顶点坐标----
/*
 *  根据标记值判断被标记点的平均值四个顶点值sign_x1(为最小的X值)，sign_x2（为最大的X值），sign_y1（为最小的Y值），sign_y2（为最大的Y值）
 */
    int sign_x1[buffer_int];
    int sign_x2[buffer_int];
    int sign_y1[buffer_int];
    int sign_y2[buffer_int];
    for(int i=0;i<buffer_int;i++)
    {
        sign_x1[i]=width;
        sign_y1[i]=height;
    }
    for(int i=0;i<buffer_int;i++)
    {
        sign_x2[i]=0;
        sign_y2[i]=0;
    }

    for(int num=0;num<buffer_int;num++)
    {
        if(sign_num[i]!=0)
        {
            for(int i=0;i<width;i++)
            {
                for(int j=0;j<height;j++)
                {
                    if(img_threshold[i][j]==sign_num[num])
                    {
                        if(i<sign_x1[num])
                        {
                            sign_x1[num]=i;
                        }
                        if(j<sign_y1[num])
                        {
                            sign_y1=j;
                        }
                        if(i>sign_x2[num])
                        {
                            sign_x2[num]=i;
                        }
                        if(j>sign_y2[num])
                        {
                            sign_y2[num]=j;
                        }
                    }
                }
            }
        }
    }

//-----------使用顶点坐标的X值，计算黄色区域，向下平移十个像素的平均灰度值------
/*
    灰度值的基本模板是img_yellow
*/
    int avg_threshold=70;
    int add_threshold=0;
    int num_threshold=0;
    for(int num=0;num<buffer_int;num++)
    {
       for(int i=sign_x1[num];i<sign_x2[num];i++)
       {
          for(int j=sign_y2[num];j<sign_y2[num]+10;j++)
          {
              num_threshold++;
              add_threshold=add_threshold+img_yellow[i][j];
          }
       }
       if(add_threshold/num_threshold<avg_threshold)
       {
           sign_x1[num]=0;
           sign_x2[num]=0;
       }
    }

//----------------最后的标记结果是读取sign_x1(为最小的X值)，sign_x2（为最大的X值），sign_y1（为最小的Y值），sign_y2（为最大的Y值）数组的值进行标记




     delete []sign_x1;
     delete []sign_x2;
     delete []sign_y1;
     delete []sign_y2;
     delete []sign_num;
     delete []img_yellow;
     delete []img_threshold;
     delete []blue_threshold;
     delete []num_bole_area;
}
