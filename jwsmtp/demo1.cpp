/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <fstream>

#include <iostream>
// Please note the jwsmtp library has to be installed
// for this next header to work.
#include "jwsmtp/jwsmtp.h"

using namespace std;

// obviously we must escape the quotes i.e. \"
std::string html("<html>"
"<body>"
"This is the html part of the message<br><br>"
"<b>bold</b><br>"
"<i>italic</i><br>"
"<font size=\"7\">Large Text</font><br><br>"
"Or a link: <a href=\"http://www.docteurordinateur.org\">docteurordinateur.org</a><br><br>"
"And an image: <br><img alt=\"an image in email\" src=\"http://www.oifii.org/do-org/dog/spi_docteur.jpg\"><br>"
"</body>"
"</html>");

int main(int argc, char* argv[])
{
	char szToAddr[255] = "";
	ifstream ToAddressFile("toaddress.txt");

	// replace the users 'to' and 'from' here before compiling this demo
	jwsmtp::mailer m("stephane.poirier@oifii.org", "stephane.pe.poirier@gmail.com", "subject line",
					"This is the plain text part of the message", "smtp.vif.com",
					jwsmtp::mailer::SMTP_PORT, false);

	// send a html file (remember you still can send an html file as an attachment
	// but calling this function will allow mime compatible clients to actually
	// display the html if the client is set to show html messages.
	//    m.setmessageHTMLfile("/home/myname/thefile.html");
   
	// Build our html from a string. You can also send html as a vector.
	// i.e.
	//    std::vector<char> htmlvec;
	//    ....add html to the vector.
	//    m.setmessageHTML(htmlvec);
	m.setmessageHTML(html);

	m.attach("toaddress.txt");
	//for(int i=0; i<15; i++)
	//{

	////////////////////////////////////////////////////////////////////////////////////////////
	// get each destination email address (using supplied text file, one email address per line)
	ToAddressFile.getline(szToAddr, sizeof(szToAddr)); //get first email address

	do //for each line of toaddress.txt ...
	{

		m.clearrecipients();
		//m.addrecipient("stephane.poirier@oifii.org");
		m.addrecipient(szToAddr);

		//m.username("someone@somewhere.net");
		//m.password("secret");
		m.send(); // send the mail
		std ::cout << m.response() << "to " << szToAddr << "\n";

		Sleep(10000);

		ToAddressFile.getline(szToAddr, sizeof(szToAddr)); //get next email address
	} while(ToAddressFile.good());

	//}
   return 0;
}
