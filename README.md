# SailHub
SailHub is an inoffical native GitHub app for Sailfish OS using GitHub GraphQL API (v4).

I made this app to familiarize myself with GraphQL API concepts. GitHub API is well documented and ideal for this purpose.

>![](icons/128x128/harbour-sailhub.png)

## Current state of development

The development is in an early state at the moment.  
Lot of functionality is missing.

## Authentication with Personal Access Token
To authenticate with GitHub API a personal access token is necessary. You can create one in developer settings on GitHub profile settings page.

![](doc/images/github_personal_access_token.png)

## Implemented Features
- Basic Markdown rendering using ShowdownJS
- Very basic notifications (using GitHub APIv3 but I am not happy with it at the moment)

## Implemented CRUD Features
Function description: [*C*]reate, [*R*]read, [*U*]pdate, [*D*]elete, [*S*]earch

- Repository [*RS*]
- Organization [*RS*]
- User [*RS*]
- Issue [*CRUD*] + close
- Comment (Issue / Pull Request) [*CRUD*]
- Pull request [*R*]
- Repository files [*R*]
- File content [*R*]
- Labels (Issue / Pull Request) [*R*]
- Reaction (Comment / Issue / Pull Request) [*RU*]
- Releases [*R*]
- Release Assets [*R*]
- Notification (Unreaded) [*R*]

## Implemented Social Features

- Follow / Unfollow user
- Watch / Star repository
- Commenting (Issue / Pull Requests)
- Reactions (Comment / Issue / Pull Request)

## Planned Features
- Code highlighting
- Gist
- Commits
- Packages
- Discussion
- Some useful cover action /content
- Feature requests (any ideas are welcome!)
- ...

## Translations
Available translations:

- English
- German
- Polish (by [atlochowski](https://github.com/atlochowski))
- Chinese (by [dashinfantry](https://github.com/dashinfantry))
  
If you missing your native language you are welcome to support this project with your translation.

[https://weblate.nubecula.org/engage/harbour-sailhub/](https://weblate.nubecula.org/engage/harbour-sailhub/)

[![https://weblate.nubecula.org/engage/harbour-sailhub/](https://weblate.nubecula.org/widgets/harbour-sailhub/-/multi-auto.svg)](https://weblate.nubecula.org/engage/harbour-sailhub/)

## Testing
If you like to test the functionality you can use my dummy repository:

[black-sheep-dev/dummy-repo](https://github.com/black-sheep-dev/dummy-repo)

## Donations

If you like my work, you can buy me a beer! 

[![PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif) ](https://www.paypal.com/paypalme/nubecula/1)

[![Liberapay](https://liberapay.com/assets/widgets/donate.svg)](https://liberapay.com/black-sheep-dev/donate)