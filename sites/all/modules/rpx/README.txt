$Id: README.txt,v 1.3 2011/02/07 12:27:43 geokat Exp $

Module:  Janrain Engage (formerly RPX)

Authors: Peat Bakke <peat@janrain.com>
         George Katsitadze <george@janrain.com>
         Nathan Rambeck <http://nathan.rambeck.org>
         Rendahl Weishar <ren@janrain.com>


Description
===========

The Janrain Engage module (formerly RPX) integrates Drupal sites with
the powerful Janrain Engage service (www.janrain.com/products/engage).
Using Janrain Engage, Drupal sites can authenticate new and existing
users with popular third-party websites, map user profile data from
these websites to Drupal fields, and share Drupal content with a
user's existing social network on multiple third-party sites. The
result is an accelerated user registration process, an enhanced
ability to gather user data, and increased site traffic from the viral
promotion of website content.

In particular, the module helps Drupal websites quickly and seamlessly
integrate with 18 social networks and service providers, including
Facebook, Twitter, Google, Yahoo!, LinkedIn, Myspace, AOL, PayPal, and
Windows Live. Instead of having to integrate with each of these
websites on your own, the Janrain Engage module (and the underlying
Janrain Engage service) do the heavy lifting for you.


Features
===========

Some notable features of the module include:

* AUTHENTICATION:  Allow site visitors to register and login with one
  of their existing accounts at popular third-party websites. Support
  is included for both the Drupal user login block and the user login
  page. Quickly and easily converting anonymous site visitors into
  active registered users.

* DATA MAPPING:  With permission of the user, you can map third-party
  user profile data to specific Drupal fields. A variety of fields
  are supported, including User fields, old-style Profile fields, and
  Profile2 contributed module fields.

* SOCIAL SHARING:  Make it easy for users to share their Drupal
  content and comments with friends and followers on other social
  networks. A "Share" button or link may be included on specific
  content types, which triggers the Janrain Engage social sharing
  widget.

* RULES INTEGRATION:  For those using the popular Rules module
  (http://drupal.org/project/rules), you can configure the full range
  of Rules-based actions to occur (change a role, send an e-mail,
  etc.) whenever a user adds or removes a third-party account via
  Janrain Engage.


Supported Third-Party Websites
===========

The Janrain Engage service currently supports the following social
networks and service providers:

Facebook
Google
LinkedIn
Myspace
Twitter
Windows Live
Yahoo!
AOL
Blogger
Flickr
Hyves
Livejournal
OpenID
MyOpenID
Netlog
PayPal
Verisign
Wordpress

Because new providers are added on a regular basis, you can view the
most current list of providers at: https://rpxnow.com/docs/providers


Installation and Configuration
============

To install and configure this module, do the following:

1. Download the module's tarball, extract its contents, and move the
   resulting "rpx" directory into your site's "modules" directory.

2. Visit admin/modules and enable the "Janrain Engage Core," "Janrain
   Engage UI," and "Janrain Engage Widgets" modules. The "Janrain
   Engage Rules integration" module is optional if you would like
   those features. All of these modules can be found within the
   "Janrain Engage" fieldset.

3. Visit admin/people/permissions and configure available module
   permissions. This includes the "Administer Janrain Engage
   settings" permission and the "Manage own 3rd party identities"
   permission.

4. If you want users to be able to create their own accounts using
   Janrain Engage, you should visit admin/config/people/accounts and
   choose "Visitors" under the "Who can register accounts?" setting.

5. Visit admin/config/people/rpx and enter your Janrain Engage API
   key. This API key must be entered for the module to function. Once
   this API key is entered, the module will automatically populate
   your "Engage Realm" and "Engage Admin URL".

6. Also at admin/config/people/rpx, configure other module settings
   related to the user interface, authentication, social sharing, and
   verification e-mails.

7. Visit admin/config/people/rpx/profile and configure Field Mapping
   if you would like third-party profile data to be mapped to Drupal
   fields. You can map data to User fields
   (admin/config/people/accounts/fields), legacy Profile fields (for
   sites that have been upgraded from Drupal 6), or Profile2
   contributed module fields (http://drupal.org/project/profile2).

8. Login as a user with the "Manage own 3rd party identities"
   permission. Each user with this permission will have a "Linked
   accounts" tab by default on their account page.

NOTE: If you don't yet have a Janrain Engage API Key, please visit
the following link to create a Janrain Engage account:

http://www.janrain.com/products/engage/get-janrain-engage

You will be able to choose from a Basic (free), Plus, Pro, or
Enterprise level account. All account types are supported by this
module.

Additionally, in order to enable sign-in with Facebook, Linkedin,
Twitter, MySpace, Paypal, and Windows Live accounts (as well as social
publishing to Facebook, Twitter, Myspace, Linkedin and Yahoo!), you
must first create a free developer account with each respective
service. Easy-to-follow links and step-by-step instructions are
provided from your account control panel on the Janrain Engage
website.


RECOMMENDED MODULES
===============

* Rules (http://drupal.org/project/rules):  Allows you to configure
  actions that occur when a linked third-party account is added or
  removed. Future development will include a social sharing action
  that allows you to post to third-party websites on other Drupal
  events.

* Profile2 (http://drupal.org/project/profile2):  Designed to be the
  successor of the core Profile module (which is deprecated for Drupal
  7), this module provides a new, fieldable "profile" entity.
  Third-party user data may be mapped directly to fields attached to
  these profile entities.


DEMO SITE
===============

You can test the latest functionality and features at:
http://plugins.janrain.com/drupal7/


DOCUMENTATION
===============

For detailed technical documentation, please visit:

* http://rpxnow.com/docs/
* http://api.drupal.org/


FAQ
===============

Q: My users get an error during registration that says "The configured
   token URL has not been whitelisted."  What should I do?

A: This is probably not a problem with the module itself. Try editing
   the app settings in your Janrain Engage account to use a wildcard
   for subdomains. So your domains would include mysite.com and also
   *.mysite.com.

Q: I want to set-up a Rules action that only happens when a user adds
   his Facebook account. How do it do this?

A: First, create a rule on the "Linked account was added" event.
   Then, create a "data comparison" condition and choose
   "rpx:provider-title" as the data to compare. Select "equals" as
   your comparison operator and enter "Facebook" as the data value.
   Any action that you now configure will only occur if the user adds
   a Facebook account. You can follow the same procedure for any
   other supported third-party website. Note that to get the same
   result you could also use "rpx:provider-machinename" as the data to
   compare and "facebook" (not capitalized) as the data value.
