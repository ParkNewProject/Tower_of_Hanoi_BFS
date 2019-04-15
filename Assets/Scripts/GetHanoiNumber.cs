using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GetHanoiNumber : MonoBehaviour
{
    public static int hanoiNumber=2;
    Button startBtn;
    Text hanoiText;
    // Start is called before the first frame update
    void Start()
    {
        startBtn = GameObject.Find("StartButton").GetComponent<Button>();
        hanoiText = GameObject.Find("HanoiText").GetComponent<Text>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }
        hanoiText.text = hanoiNumber.ToString();

    }

    public void OnCountUp()
    {
        Debug.Log("Clicked CountUp Btn");
        if (hanoiNumber < 8)
        {
            hanoiNumber++;
            Debug.Log("hanoiNumber : " + hanoiNumber);
        }
            
        
    }
    public void OnCountDown()
    {
        Debug.Log("Clicked CountDown Btn");
        if (hanoiNumber > 2)
        {
            hanoiNumber--;
            Debug.Log("hanoiNumber : " + hanoiNumber);
        }
    }
}
