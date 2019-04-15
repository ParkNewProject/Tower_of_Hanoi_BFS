using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ChangeScenes : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
       
    }
    public void OnChangeScenes()
    {
        Debug.Log("Clicked Start Button, OnChangeScenes() is working...");
        SceneManager.LoadScene("SampleScene");
    }
}
