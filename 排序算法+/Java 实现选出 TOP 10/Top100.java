//
// java �ö�ʵ�ֲ��� TOP 10
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
		int number = 100000000;// һ�ڸ���
		int maxnum = 1000000000;// ��������ֵ
		int i = 0;
		int topnum = 100;// ȡ���Ķ��ٸ�
	 
		Date startTime = new Date();
		
		Random random = new Random();
		int[] top = new int[topnum];
		for (i = 0; i < topnum; i++) {
			top[i] = Math.abs(random.nextInt(maxnum));//����Ϊ�����
//			top[i] = getNum(i);
		}

		buildHeap(top, 0, top.length);// ������С�ѣ� top[0]Ϊ��СԪ��
		for (i = topnum; i < number; i++) {

			int currentNumber2 = Math.abs(random.nextInt(maxnum));//����Ϊ�����
//			int currentNumber2 = getNum(i);
			// ���� top[0]�򽻻�currentNumber2  �ع���С��
			if (top[0] < currentNumber2) {
				top[0] = currentNumber2;
				shift(top, 0, top.length, 0); // ������С�� top[0]Ϊ��СԪ��
			}
		}
		System.out.println(Arrays.toString(top));
		sort(top);
		System.out.println(Arrays.toString(top));
		
		Date endTime = new Date();
		System.out.println("����"+(endTime.getTime() - startTime.getTime())+"����");
 
	}
	
	public static int getNum(int i){
		return i;
	}

 
	//������������
	public static void buildHeap(int[] array, int from, int len) {
		int pos = (len - 1) / 2;
		for (int i = pos; i >= 0; i--) {
			shift(array, from, len, i);
		}
	}
 
	/**
	 * @param array top����
	 * @param from ��ʼ
	 * @param len ���鳤��
	 * @param pos ��ǰ�ڵ�index
	 * */
	public static void shift(int[] array, int from, int len, int pos) {
		// ����ýڵ��ֵ 
		int tmp = array[from + pos];

		int index = pos * 2 + 1;// �õ���ǰpos�ڵ����ڵ�
		while (index < len)//  ������ڵ�
		{
			if (index + 1 < len
					&& array[from + index] > array[from + index + 1])// ��������ҽڵ�
			{
				// ����ұ߽ڵ����߽ڵ�С���ͺ��ұߵıȽ�
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
		// ����ȫ���û���Ϻ� ������ʱ�����������Ľڵ�
		array[from + pos] = tmp;
	}
	
	public static void sort(int[] array){  
        for(int i = 0; i < array.length - 1; i++){  
            //��ǰֵ������Сֵ  
            int min = array[i];  
            for(int j = i+1; j < array.length; j++){  
                if(min>array[j]){  
                    //��������б�minֵ��С�ľͽ���  
                    min = array[j];  
                    array[j] = array[i];  
                    array[i] = min;  
                }  
            }  
        }  
    }

}
