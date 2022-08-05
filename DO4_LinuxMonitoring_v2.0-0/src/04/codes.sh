code=(200 201 400 401 403 404 500 501 502 503)
#OK 200
#The request was fulfilled.
#
#CREATED 201
#Following a POST command, this indicates success, but the textual part of the 
#response line indicates the URI by which the newly created document should be 
#known.
#
#Bad request 400
#The request had bad syntax or was inherently impossible to be satisfied.
#
#Unauthorized 401
#The parameter to this message gives a specification of authorization schemes 
#which are acceptable. The client should retry the request with a suitable 
#Authorization header.
#
#PaymentRequired 402
#The parameter to this message gives a specification of charging schemes 
#acceptable. The client may retry the request with a suitable ChargeTo header.
#
#Forbidden 403
#The request is for something forbidden. Authorization will not help.
#
#Not found 404
#The server has not found anything matching the URI given
#
#Internal Error 500
#The server encountered an unexpected condition which prevented it from fulfilling 
#the request.
#
#Not implemented 501
#The server does not support the facility required.
#
#Bad Gateway 502
#
#Service Unavailiable 503


method=(GET POST PUT PATCH DELETE)

agent=("Mozilla" "Google Chrome" "Opera" "Safari" "Internet Explorer" "Microsoft Edge" "Crawler and bot" "Library and net tool")
