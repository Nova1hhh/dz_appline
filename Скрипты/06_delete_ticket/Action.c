Action()
{
	lr_start_transaction("06_delete_ticket");

 	web_reg_save_param_ex(
		"ParamName=userSession",
		"LB=name=\"userSession\" value=\"",
		"RB=\"/>",
		"Ordinal=1",
		SEARCH_FILTERS,
		LAST);
	
	lr_start_transaction("main_page");
	
	web_reg_find("Text= A Session ID has been created and loaded",
		LAST);
	
	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("main_page", LR_AUTO);
	
	lr_think_time(5);

	lr_start_transaction("login");
	
	web_reg_find("Text=User password was correct",
		LAST);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t12.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=login.x", "Value=0", ENDITEM,
		"Name=login.y", "Value=0", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("click_itinerary_button");

	web_reg_save_param("f_ID",
		"LB=name=\"flightID\" value=\"",
		"RB=\"  />",
		"Ord=ALL",
		LAST);
	
	web_reg_find("Text=User wants the intineraries.",
		LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_itinerary_button",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("delete_ticket");
	
	web_reg_find("Fail=Found",
		"Text={f_ID_1}",
		LAST);

	web_submit_form("itinerary.pl",
		"Snapshot=t14.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM,         
		"Name=removeFlights.x", "Value=5", ENDITEM, 
		"Name=removeFlights.y", "Value=9", ENDITEM, 
		LAST);

	lr_end_transaction("delete_ticket",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("logout");

	web_reg_find("Text/IC= A Session ID has been created",
		LAST);
	
	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("06_delete_ticket", LR_AUTO);
	
	return 0;
}