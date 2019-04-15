using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;

public class MainObject : MonoBehaviour
{
  
    public GameObject[] cylinder;

    Queue<int[][]> q = new Queue<int[][]>();
    Stack<int> s = new Stack<int>();

    int n = 0;          // index of son
    int m = -1;         // index of parent

    public int hanoiNumber;   // height of hanoi tower (Problem - Size)

    int[][][] G_List;
    int[] G_Parent;
    int size_glist;


    bool working = false;   // don't update at the same time
    int a;

    void Moving()
    {
        int[][] firstArr = new int[3][];
        int[][] goalArr = new int[3][];
        int[][] currentArr;
        int[][] arr;

        // init rows
        for (int i = 0; i < 3; i++)
        {
            firstArr[i] = new int[hanoiNumber];
            goalArr[i] = new int[hanoiNumber];

        }
        // init columns
        for (int i = 0; i < hanoiNumber; i++)
        {
            firstArr[0][i] = hanoiNumber - i;
            goalArr[2][i] = hanoiNumber - i;
        }

        for (int i = 1; i < 3; i++)
            for (int j = 0; j < hanoiNumber; j++)
                firstArr[i][j] = 0;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < hanoiNumber; j++)
                goalArr[i][j] = 0;
        Put_G_List(firstArr);
        q.Enqueue(firstArr);

        // i: start, j: arrive
        while (q.Count != 0)
        {
            currentArr = q.Dequeue();
            m++;
            int cnt = 0;
            //check goalstate
            for (int i = 0; i < hanoiNumber; i++)
            {
                if (currentArr[2][i] == goalArr[2][i]) cnt++;
            }
            if (cnt == hanoiNumber)
            {
                // parent->son printArr

                s.Push(m);
                while (m != 0)
                {
                    s.Push(G_Parent[m]);
                    m = G_Parent[m];
                }
                return;
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        // copy
                        arr = CopyArr(currentArr);
                        if (i != j) Sons(i, j, arr);
                    }
                }
            }
        }
        return;
    }

    void Sons(int i, int j, int[][] arr)
    {
        int from;
        int to;

        // start: [i,from]
        for (from = hanoiNumber - 1; from >= 0; from--)
            if (arr[i][from] != 0) break;

        // arrive: [j,to]
        for (to = hanoiNumber - 1; to >= 0; to--)
            if (arr[j][to] != 0) break;
        to++;

        // do not start
        if (from < 0)
        {
            return;
        }

        // index of arrive is not 0, check idx-1
        if (to != 0)
        {
            if (arr[j][to - 1] <= arr[i][from])
            {
                return;
            }
        }
        int temp = arr[i][from];
        arr[j][to] = temp;
        arr[i][from] = 0;
        if (!Equal_G_List(arr))
        {
            Put_G_List(arr);
            q.Enqueue(arr);
        }
    }

    int[][] CopyArr(int[][] a)
    {
        int[][] copy = new int[3][];
        for (int i = 0; i < 3; i++)
        {
            copy[i] = new int[hanoiNumber];
            for (int j = 0; j < hanoiNumber; j++)
            {
                copy[i][j] = a[i][j];
            }
        }
        return copy;
    }

    void Put_G_List(int[][] a)
    {
        G_List[n] = new int[3][];
        for (int i = 0; i < 3; i++)
        {
            G_List[n][i] = new int[hanoiNumber];
            for (int j = 0; j < hanoiNumber; j++)
            {
                G_List[n][i][j] = a[i][j];
            }
        }
        G_Parent[n] = m;
        n++;
    }

    bool Equal_G_List(int[][] a)
    {
        int cnt = 0;
        for (int x = 0; x < n;)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < hanoiNumber; j++)
                {
                    if (G_List[x][i][j] == a[i][j])
                    {
                        cnt++;
                    }
                }
            }
            if (cnt == hanoiNumber * 3) return true;
            else
            {
                x++;
                cnt = 0;
            }
        }
        return false;
    }

    void PrintArr(int[][] a)
    {
        float dirX = -15.0f;
        float dirY = 0.0f;
        float dirZ = 0.0f;
        for (int i = 0; i < 3; i++)
        {

            for (int j = 0; j < hanoiNumber; j++)
            {

                if (a[i][j] != 0)
                {
                    Debug.Log("i, j, (a[i][j]-1) : " + i + " " + j + " " + (a[i][j]-1));
                    Debug.Log("dirX, dirY, dirZ: " + dirX + " " + dirY + " " + dirZ);
                    cylinder[a[i][j] - 1].transform.position = new Vector3(dirX, dirY, dirZ);
                    
                    
                }
                dirY = dirY + 0.6f;
            }
            dirY = 0;
            dirX = dirX + 15.0f;
        }
        dirX = -15.0f;
        dirY = 0.0f;
       dirZ = 0.0f;
    }

    // Start is called before the first frame update
    void Start()
    {
        working = true;

        hanoiNumber = GetHanoiNumber.hanoiNumber;
        cylinder = new GameObject[8];
        for (int j = 0; j < 8; j++)
        {
            cylinder[j] = GameObject.Find("Cylinder" + (j + 1));
            if (j >= hanoiNumber)
            {
                Destroy(cylinder[j]);
            }
        }
        Debug.Log("hanoiNumber : " + hanoiNumber);

        size_glist = (int)Math.Pow(3, hanoiNumber);
        G_List = new int[size_glist][][];
        G_Parent = new int[size_glist];

        Moving();
        working = false;

        StartCoroutine(Drawing());
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }
    }

    IEnumerator Drawing()
    {
       
        if (working == false)
        {
            working = true;
            do
            {

                Debug.Log("s.Count : " + s.Count);
                a = s.Pop();
                PrintArr(G_List[a]);
                yield return new WaitForSeconds(0.5f);
            } while (s.Count != 0);
            working = false;
        }
    }
}
