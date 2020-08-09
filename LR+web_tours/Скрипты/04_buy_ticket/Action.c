 Action()
{

	lr_start_transaction("04_buy_ticket");

/*Correlation comment - Do not change!  Original value='129193.318023491zztfDiVpcQfiDDDDDQiHcpciHHHf' Name ='userSession' Type ='ResponseBased'*/


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

	web_reg_find("Text/IC=User password was correct",
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
		"Name=login.x", "Value=0", ENDITEM,
		"Name=login.y", "Value=0", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("click_flights");

	web_reg_find("Text/IC=Search Flights Button",
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
	
	web_reg_find("Text/IC=Flight Selections",
		LAST);

/*Correlation comment - Do not change!  Original value='632;82;07/15/2020' Name ='outboundFlight' Type ='ResponseBased'*/
//	web_reg_save_param_attrib(
//		"ParamName=outboundFlight",
//		"TagName=input",
//		"Extract=value",
//		"Name=outboundFlight",
//		"Type=radio",
//		SEARCH_FILTERS,
//		"IgnoreRedirections=No",
//		LAST);
		
	web_reg_save_param("outboundFlight",
		"LB=name=\"outboundFlight\" value=\"",
		"RB=\"",
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
		"Name=departDate", "Value={depart_date_new}", ENDITEM, 
		"Name=arrive", "Value={arrival_city}", ENDITEM, 
		"Name=returnDate", "Value={return_date_new}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seat_pref}", ENDITEM, 
		"Name=seatType", "Value={seat_type}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=43", ENDITEM, 
		"Name=findFlights.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("fill_forms",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("choose_flight");
	
	web_reg_find("Text/IC=Flight Reservation",
		LAST);

	web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t5.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seat_type}", ENDITEM,
		"Name=seatPref", "Value={seat_pref}", ENDITEM,
		"Name=reserveFlights.x", "Value=22", ENDITEM,
		"Name=reserveFlights.y", "Value=7", ENDITEM,
		LAST);

	lr_end_transaction("choose_flight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("fill_payment_details");

	web_reg_find("Text/IC=Thank you for booking",
		LAST);

	web_reg_find("Text=from {depart_city} to {arrival_city}",
		LAST);

	web_submit_data("reservations.pl_3",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t6.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=firstName", "Value={name}", ENDITEM,
		"Name=lastName", "Value={surname}", ENDITEM,
		"Name=address1", "Value={address}", ENDITEM,
		"Name=address2", "Value={city}", ENDITEM,
		"Name=pass1", "Value={name} {surname}", ENDITEM,
		"Name=creditCard", "Value={card_num}", ENDITEM,
		"Name=expDate", "Value={exp_date}", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatType", "Value={seat_type}", ENDITEM,
		"Name=seatPref", "Value={seat_pref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		"Name=buyFlights.x", "Value=67", ENDITEM,
		"Name=buyFlights.y", "Value=8", ENDITEM,
		LAST);

	lr_end_transaction("fill_payment_details",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("logout");

	web_reg_find("Text/IC= A Session ID has been created",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("04_buy_ticket", LR_AUTO);

	return 0;
}