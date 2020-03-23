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

//--------------------计算兴趣区域的面积和数量，判断连通域的算子是3x3--------

     for(int i=0;i<width;i++)
     {
         for(int j=0;j<height;j++)
         {
            if(img_threshold[i][j]==255)
            {
                for(int element_i=0;element_i<3;element_i++)
                {
                    for(int element_j=0;element_j<3;element_j++)
                    {
                        if((i-1+element_i>0)&(j-1+element_j>0))
                        {
                            if(img_threshold[i-1+element_i][j-1+element_j]==255)
                            {

                            }
                        }
                    }
                 }
            }
          }
      }



     delete []img_yellow;
     delete []img_threshold;
     delete []blue_threshold;
}
