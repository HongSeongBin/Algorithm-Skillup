import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main{
	public static void main(String[] args) throws Exception
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String input = br.readLine();
		StringTokenizer st = new StringTokenizer(input);
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int answer = 0;
//		int[] shark_weight = new int[k+1]; // ��ȣ�� ����� ���� ������ 0
		HashMap<Integer,Integer>[] turn_odd = new HashMap[m+1];	// 1,2�� ��ġ -> [1]�� <2,��� ��ȣ>�� ǥ��
		HashMap<Integer,Integer>[] turn_even = new HashMap[m+1];	// 1,2�� ��ġ -> [1]�� <2,��� ��ȣ>�� ǥ��
		shark[] state = new shark[k];	 //��� ����

		for(int i = 1; i <=m; i++)
		{
			turn_odd[i] = new HashMap();
			turn_even[i] = new HashMap();
		}

		for(int c = 0 ; c < k; c++)
		{
			input = br.readLine();
			st = new StringTokenizer(input);
			int y = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int l = Integer.parseInt(st.nextToken());
			int p = Integer.parseInt(st.nextToken());
			int w = Integer.parseInt(st.nextToken());
			turn_odd[x].put(y, c);
			shark s = new shark(x,y,w,p,l,c);
			state[c] = s;
		}		
		int turn = 0;
		for(int c = 1; c<=m; c++)	//�� ���� Ƚ��
		{
			turn^= 1;
			int catched_shark = -1;
			
			if(turn == 1)
			{
				if(turn_odd[c].size() != 0)	//��� ���� ��
				{
//					Set<Integer> gotcha = turn_odd[c].keySet();
//					if(gotcha == null)
//						break;
//					Iterator it = gotcha.iterator();
//					int key =(int)it.next();
					int key = 1;
					for(;key<=n; key++)
					{
						if(turn_odd[c].get(key)== null)
							continue;
						else
							break;
					}
					if(key <= n)
					{
					catched_shark = turn_odd[c].get(key);	//�ش� ��� �ε��� �̾ƿ;���.				
					turn_odd[c].remove(key);	// �ʿ����� ����
					answer+= state[catched_shark].weight;
					}
				}
			}
			else
			{
				if(turn_even[c].size() != 0)	//��� ���� ��
				{
//					Set<Integer> gotcha = turn_even[c].keySet();
//					if(gotcha == null)
//						break;
//					Iterator it = gotcha.iterator();
//					int key =(int)it.next();
					int key = 1;
					for(;key<=n; key++)
					{
						if(turn_even[c].get(key)== null)
							continue;
						else
							break;
					}
					if(key <= n)
					{
					catched_shark = turn_even[c].get(key);	//�ش� ��� �ε��� �̾ƿ;���.				
					turn_even[c].remove(key);	// �ʿ����� ����
					answer+= state[catched_shark].weight;
					}
				}				
			}
			if(catched_shark != -1)
			state[catched_shark] = null;
//			shark_weight[catched_shark] = 0 ;				
			
			for(int move_idx = 0; move_idx< k; move_idx++ )				//�̹��� ������ ��� ��ȣ
			{
				if(state[move_idx] == null)
					continue;
				
				shark move_shark = state[move_idx];
				int temp_y = move_shark.y;
				int temp_x = move_shark.x;
				int temp_l = move_shark.len;
				int temp_p = move_shark.position;
				int remain = temp_l;
				if(turn == 1)
					turn_odd[temp_x].remove(temp_y);	//�� �ڿ�
				else
					turn_even[temp_x].remove(temp_y);

				while(remain > 0)				//�̵�
				{
					switch(temp_p)
					{
					case 1:		// ��
						if(remain< temp_y )
						{
							temp_y -= remain;
							remain = 0;
						}
						else
						{
						remain-= (temp_y-1);
						temp_y = 1;
						temp_p = 2;
						}
						break;
					case 2:	//�Ʒ�
						if( n-temp_y >= remain )
						{
							temp_y += remain;
							remain = 0;
						}
						else
						{
						remain -= (n-temp_y);
						temp_y = n;
						temp_p = 1;						
						}
						break;
					case 3:	//������
						if( m-temp_x >= remain )
						{
							temp_x += remain;
							remain = 0;
						}
						else
						{
						remain -= (m-temp_x);
						temp_x = m;
						temp_p = 4;						
						}
						break;
					case 4:	//����
						if(remain< temp_x )
						{
							temp_x -= remain;
							remain = 0;
						}
						else
						{
						remain-= (temp_x-1);
						temp_x = 1;
						temp_p = 3;
						}
						break;				
					}
				}
				if(turn == 1) //even�ʿ� ����
				{
					//���� ��ȭ					
					//�Ѹ����� ��� ������.
					if(turn_even[temp_x].get(temp_y)!= null)
					{			
						int already_shark = turn_even[temp_x].get(temp_y);
						if(state[already_shark].weight < move_shark.weight)
						{
							turn_even[temp_x].put(temp_y,move_idx );							
							state[already_shark] = null;
							
							state[move_idx].x = temp_x;
							state[move_idx].y = temp_y;
							state[move_idx].position = temp_p;					
						}
						else
							state[move_idx] = null;

					}
					else
					{
						turn_even[temp_x].put(temp_y, move_idx);
						state[move_idx].x = temp_x;
						state[move_idx].y = temp_y;
						state[move_idx].position = temp_p;					
					}
				}
				else
				{
					//���� ��ȭ
					//�Ѹ����� ��� ������.
					if(turn_odd[temp_x].get(temp_y)!= null)
					{			
						int already_shark = turn_odd[temp_x].get(temp_y);
						if(state[already_shark].weight < move_shark.weight)
						{
							turn_odd[temp_x].put(temp_y,move_idx );							
							state[already_shark] = null;
							
							state[move_idx].x = temp_x;
							state[move_idx].y = temp_y;
							state[move_idx].position = temp_p;					
						}
						else
							state[move_idx] = null;
					}
					else
					{
						turn_odd[temp_x].put(temp_y, move_idx);

						state[move_idx].x = temp_x;
						state[move_idx].y = temp_y;
						state[move_idx].position = temp_p;					
					}					
				}
			}			
		}
		System.out.println(answer);
	}
}
class shark
{
	int idx;
	int x;
	int y;
	int weight;
	int position;
	int len;

	shark(int i1, int i2, int i3, int i4, int i5, int i6)
	{
		x = i1;
		y = i2;
		weight = i3;
		position = i4;
		len = i5;
		idx = i6;
	}
}

class myComparator implements Comparator<shark>
{
	@Override
	public int compare(shark o1, shark o2) {
		if(o1.y < o2.y)
			return -1;
		else if (o1.y < o2.y)
			return 1;
		else 
			return 0;
	}
}

