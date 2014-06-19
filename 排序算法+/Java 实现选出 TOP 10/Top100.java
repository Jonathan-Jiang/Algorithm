//
// java 用堆实现查找 TOP 10
//

package com.my.util;

import java.util.Arrays;
import java.util.Date;
import java.util.Random;

public class Top100 {
	
	public static void main(String[] args) {
		find();
	}
	public static void find( ) {//
		int number = 100000000;// 一亿个数
		int maxnum = 1000000000;// 随机数最大值
		int i = 0;
		int topnum = 100;// 取最大的多少个
	 
		Date startTime = new Date();
		
		Random random = new Random();
		int[] top = new int[topnum];
		for (i = 0; i < topnum; i++) {
			top[i] = Math.abs(random.nextInt(maxnum));//设置为随机数
//			top[i] = getNum(i);
		}

		buildHeap(top, 0, top.length);// 构建最小堆， top[0]为最小元素
		for (i = topnum; i < number; i++) {

			int currentNumber2 = Math.abs(random.nextInt(maxnum));//设置为随机数
//			int currentNumber2 = getNum(i);
			// 大于 top[0]则交换currentNumber2  重构最小堆
			if (top[0] < currentNumber2) {
				top[0] = currentNumber2;
				shift(top, 0, top.length, 0); // 构建最小堆 top[0]为最小元素
			}
		}
		System.out.println(Arrays.toString(top));
		sort(top);
		System.out.println(Arrays.toString(top));
		
		Date endTime = new Date();
		System.out.println("用了"+(endTime.getTime() - startTime.getTime())+"毫秒");
 
	}
	
	public static int getNum(int i){
		return i;
	}

 
	//构造排序数组
	public static void buildHeap(int[] array, int from, int len) {
		int pos = (len - 1) / 2;
		for (int i = pos; i >= 0; i--) {
			shift(array, from, len, i);
		}
	}
 
	/**
	 * @param array top数组
	 * @param from 开始
	 * @param len 数组长度
	 * @param pos 当前节点index
	 * */
	public static void shift(int[] array, int from, int len, int pos) {
		// 保存该节点的值 
		int tmp = array[from + pos];

		int index = pos * 2 + 1;// 得到当前pos节点的左节点
		while (index < len)//  存在左节点
		{
			if (index + 1 < len
					&& array[from + index] > array[from + index + 1])// 如果存在右节点
			{
				// 如果右边节点比左边节点小，就和右边的比较
				index += 1;
			}
			 
			if (tmp > array[from + index]) {
				array[from + pos] = array[from + index];
				pos = index;
				index = pos * 2 + 1;
			} else {
				break;
			}
		}
		// 最终全部置换完毕后 ，把临时变量赋给最后的节点
		array[from + pos] = tmp;
	}
	
	public static void sort(int[] array){  
        for(int i = 0; i < array.length - 1; i++){  
            //当前值当作最小值  
            int min = array[i];  
            for(int j = i+1; j < array.length; j++){  
                if(min>array[j]){  
                    //如果后面有比min值还小的就交换  
                    min = array[j];  
                    array[j] = array[i];  
                    array[i] = min;  
                }  
            }  
        }  
    }

}
