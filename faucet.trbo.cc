﻿//============================================//
//script by: sstyxx01
//Version 1 - 6-22-20 1am
//============================================//

using System;
using FaucetCollector.Script;

public class TRBOFaucet : FaucetScript
{
    /// <summary>
    /// List of Settings that will be shown in the bot when selecting this Faucet in the bot.
    /// You can get the value the user entered with the methods: GetSetting("[Name of the FaucetSetting]"), GetBoolSetting and GetDateTimeSetting
    /// You can also create a new setting value using SetSetting("[Name you want to use]", "value")
    /// </summary>
    public override FaucetSettings Settings
    {
        get
        {
            return new FaucetSettings("https://faucet.trbo.cc")
            {
                new FaucetSetting(){Name="User",Type=EditorType.TextBox,Required=true,Display="Wallet TRBO"}
                //insert user settings here
                //new FaucetSetting { 
                //    Name = "Name of your setting", 
                //    Display = "Display shown in Faucet Collector", 
                //    Type = EditorType.TextBox | EditorType.Password | EditorType.CheckBox | EditorType.Wallet | EditorType.Numeric | EditorType.ComboBox | EditorType.CheckComboBox, 
                //    Required = true | false, 
                //    Default = "Optionally a default value" | true | false | null.
                //    Items = new List<string> { "item1", "item2" } (only valid for ComboBox or CheckComboBox)
                //} 
            };
        }
    }

    /// <summary>
    /// This method gets called when the faucet is enabled and the GO button is clicked
    /// </summary>
    public override void Start()
    {
        //Title that shows in the browser. Is used to identify and close popup windows
        Title = "TRBO Community Faucet";

        //After we did try to claim on the faucet we search for these elements to determine if it was a success or a fail
        SuccessXPath = "//span[contains(text(),'Success')]";
        FailXPath = "//span[@data-notify='message' and not(contains(text(),'Success'))]";

        //Let Faucet Collector start up everything
        base.Start();
    }

    /// <summary>
    /// This is the first method to run after the browser is opened and the first page is loaded.
    /// </summary>
    public override int DoInit()
    {
        //Let Faucet Collector continue.
        return base.DoInit();
    }

    /// <summary>
    /// This method gets called after the Start method, here you need to return if we are logged in or not.
    /// If you return false then it will call the BeforeLogin, Login and AfterLogin methods so you can login.
    /// After those Login methods are called it will call this IsLoggedIn method again to see if the login did succeed.
    /// If you return true Faucet Collector will store all cookies so it will probably be already logged in on the next attempt.
    /// </summary>
    public override bool IsLoggedIn()
    {
        //In here we can check for the presence of an element that is only present when you are logged in.
        //In this case we check for en element with the class "loggedIn"
        return true;
    }

    /// <summary>
    /// This method gets called if IsLoggedIn returned false, right before the DoLogin method is called.
    /// </summary>
    public override int BeforeLogin()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.BeforeLogin();
    }

    /// <summary>
    /// This method gets called after BeforeLogin, but only if IsLoggedIn returned false.
    /// It can be used to actually login the user/enter wallet details in the faucet
    /// </summary>
    /// <returns></returns>
    public override int DoLogin()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.DoLogin();
    }

    /// <summary>
    /// This method gets called after the DoLogin method.
    /// </summary>
    public override int AfterLogin()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.AfterLogin();
    }

    /// <summary>
    /// This method gets called after the login methods are successful, so we are logged into the faucet.
    /// If the faucet is not yet ready to claim you should return a TimeStamp value to return how long it takes before the Faucet claim can be done.
    /// This is used to pause the script while the faucet its timer runs out.
    /// Return the number of seconds the bot should wait.
    /// </summary>
    public override int GetFaucetWaitTime()
    {
        //let Faucet Collector continue.
        return base.GetFaucetWaitTime();
    }

    /// <summary>
    /// This method is called right before a captcha will be solved. 
    /// If you call SolveCaptcha() in other methods it will start this flow and tries to solve the captcha on the page.
    /// </summary>
    public override int BeforeSolveCaptcha()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.BeforeSolveCaptcha();
    }

    /// <summary>
    /// This method gets called after BeforeSolveCaptcha and it does the actual captcha solving
    /// It will automatically try to see if there is a SolveMedia captcha active or a reCAPTCHA active. 
    /// If it finds either one it will then use the selected method on the Captcha tab of FaucetCollector to solve the Captcha.
    /// </summary>
    public override int DoSolveCaptcha()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.DoSolveCaptcha();
    }

    /// <summary>
    /// This method will get called after DoSolveCaptcha returned it was a success.
    /// </summary>
    /// <returns></returns>
    public override int AfterSolveCaptcha()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.AfterSolveCaptcha();
    }

    /// <summary>
    /// This method is called right before we attempt to claim on the faucet. So we are logged in and good to go.
    /// Next methods that will be called are DoSolveFaucet, AfterSolveFaucet and CheckFaucetResult.
    /// </summary>
    public override int BeforeSolveFaucet()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.BeforeSolveFaucet();
    }

    /// <summary>
    /// This method gets called after the BeforeSolveFaucet. You can do the actual claiming of the faucet in here.
    /// </summary>
    /// <returns></returns>
    public override int DoSolveFaucet()
    {
        var WalletBox = ElementByXPath("//input[@type='text']");
        if (!IsVisible(WalletBox))
{
            return Fail("Wallet box is not visible");
        }

        SetText(WalletBox, GetSetting("User"));
        Wait();
        var ButtonSubmit = ElementByXPath("//button[@id='send']");
        if (!IsVisible(ButtonSubmit))
        {
            return Fail("Button submit not found");
        }
        var result = DoSolveCaptcha();
        if (result > 0)
        {
            return Fail("Button submit not found");
        }
        Click(ButtonSubmit);
        Wait();

        CheckFaucetResult();

        return GetWaitSetting();

        
    }

    /// <summary>
    /// This method will get called after the DoSolveFaucet is completed and returned it was a success.
    /// For example you can wait for a processing popup to go away until actual faucet claim result is on the page.
    /// </summary>
    public override int AfterSolveFaucet()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.AfterSolveFaucet();
    }

    /// <summary>
    /// This method gets called in the end after the BeforeSolveFaucet/DoSolveFaucet and AfterSolveFaucet methods were done.
    /// The base.CheckFaucetResult will try to find a visible element on the page using the XPath from SuccessXPath and FailXPath (see the Start method)
    /// These properties should contain XPath expressions to find certain elements on the page.
    /// For example if it finds one of the elements from the SuccessXPath, and it is visible, then it will flag the claim attempt as a success.
    /// Or if it finds one of the elements from the FailXPath, and it is visible, then it will flag the claim attempt as a failure.
    /// </summary>
    public override int CheckFaucetResult()
    {
        //This faucet has nothing to do here. We will let Faucet Collector handle it.
        return base.CheckFaucetResult();
    }
}
