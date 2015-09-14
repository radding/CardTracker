# [CardTracker](http://devpost.com/software/card-tracker)

##### MHacks 6 Winner:  Best Use of Capital One API

![fraud](http://www.memetics.com/wp-content/uploads/2013/04/Credit-Card-Fraud.jpg)

# Inspiration

Walking into MHacks 6, our team wanted to stretch our knowledge of **machine vision**
while utilizing Capital One's redesigned API *fresh off the stack*.  Interestingly 
enough, we came across a [philipino twitter account](https://twitter.com/needadebitcard)
that mockingly retweets others' postings with exposed debit card information under the credo: *need a debit card?*

Now that online banking and transactions are commonplace, we cannot afford to let one mistake compromise a user's 
account.  This technology isn't a consumer-ready application as much as a potential service for financial institutions 
to **help combat fraud**.  Fraud costs banks heavily in time, money, and personel- not to mention **reputation**-
and that isn't even considering how hard the victim has to stomach it.

Our service simply offers banking instutions *preventative measures* by beating malicious hackers to the source.

# Behind The Scenes

* Pointed at any base url, our *python* web crawlers and scrapers will retrieve every image url from every 
linked page nested within the base url.
* Afterwards, image urls are sent to the *c++* image processing module that will 
retrieve any discernable alphanumeric characters from them thanks to a synthesis between *openCV* and *tesseract-ocr*.
* Appropriate banking institution will be notified of account's compromised status (i.e. *Capital One*).
* And more! (I just know the most about how my specific modules operate)
