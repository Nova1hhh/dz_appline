Action()
{

	lr_start_transaction("03_find_flight");

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
		"Snapshot=t1.inf", 
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
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=login.x", "Value=51", ENDITEM,
		"Name=login.y", "Value=15", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("click_flights");

	web_reg_find("Text= User has returned to the search page",
		LAST);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_flights",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("fill_forms");

	web_reg_find("Text=Flight Selections",
		LAST);

	web_reg_find("Text=Flight departing from <B>{depart_city}</B> to <B>{arrival_city}</B>",
		LAST);

	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depart_city}", ENDITEM, 
		"Name=departDate", "Value={depart_date}", ENDITEM, 
		"Name=arrive", "Value={arrival_city}", ENDITEM, 
		"Name=returnDate", "Value={return_date}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seat_pref}", ENDITEM, 
		"Name=seatType", "Value={seat_type}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=50", ENDITEM, 
		"Name=findFlights.y", "Value=3", ENDITEM, 
		LAST);

	lr_end_transaction("fill_forms",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("logout");

	web_reg_find("Text=A Session ID has been created",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("03_find_flight", LR_AUTO);

	return 0;
}