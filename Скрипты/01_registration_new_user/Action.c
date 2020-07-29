Action()
{

	lr_start_transaction("01_registration_new_user");
	
	lr_start_transaction("main_page");
	
	web_reg_find("Text= A Session ID has been created and loaded",
		LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("main_page", LR_AUTO);

	lr_think_time(5);
	
	lr_start_transaction("go_to_regpage");
	
	web_reg_find("Text=First time registering? Please complete the form below",
		LAST);

	web_url("sign up now", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_regpage",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("registration");

	web_reg_find("Text=Welcome to Web Tours",
		LAST);

	web_submit_data("login.pl", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={name}", ENDITEM, 
		"Name=lastName", "Value={surname}", ENDITEM, 
		"Name=address1", "Value={address}", ENDITEM, 
		"Name=address2", "Value={city}", ENDITEM, 
		"Name=register.x", "Value=58", ENDITEM, 
		"Name=register.y", "Value=6", ENDITEM, 
		LAST);

	lr_end_transaction("registration",LR_AUTO);

	lr_think_time(5);

	web_reg_find("Text=User has returned to the home page",
		LAST);

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_think_time(22);

	lr_start_transaction("logout");
	
	web_reg_find("Text= A Session ID has been created",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("01_registration_new_user", LR_AUTO);

	return 0;
}