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

## Dependencies (EMOJI)
This package depends on an emoji pack I released on OpenRepos using the emojis from [Twitter Emoji](https://twemoji.twitter.com/) project.  
I decided to split the emoji assets from the main app to reduce app size.
Shipping these assets with every app release makes no sence.
The installation should happen automatically.

## Implemented Features
- Basic Markdown rendering using ShowdownJS
- Very basic notifications (using GitHub APIv3 but I am not happy with it at the moment)

## Implemented CRUD Features
Function description: [*C*]reate, [*R*]read, [*U*]pdate, [*D*]elete, [*S*]earch

- Assignee (Issue / Pull Request) [*CRUD*]
- Comment (Issue / Pull Request) [*CRUD*]
- File content [*R*]
- Gists [*R*]
- Issue [*CRUD*] + close
- Labels (Issue / Pull Request) [*R*]
- Notification (Unreaded) [*R*]
- Organization [*RS*]
- Pull request [*R*]
- Reaction (Comment / Issue / Pull Request) [*RU*]
- Releases [*R*]
- Release Assets [*R*]
- Repository [*RS*]
- Repository files [*R*]
- User [*RS*]
- Discussions [*CRUD*]
- Discussion Comments [*CRUD*]

## Implemented Social Features

- Follow / Unfollow user
- Watch / Star repository
- Commenting (Issue / Pull Requests)
- Reactions (Comment / Issue / Pull Request)
- Discussion (Comment / Reply ) on Repositories (when activated)
- Sponsoring / Funding

## Administrative Features

- Assign users to issues and pull requests

## Planned Features
- Code highlighting
- Commits
- Packages
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

## Attribution
This projects uses the emoji from [Twitter Emoji (twemoji)](https://twemoji.twitter.com/) - Graphics licensed under CC-BY 4.0

## Donations

If you like my work, you can buy me a beer! 

[![PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif) ](https://www.paypal.com/paypalme/nubecula/1)

[![Liberapay](https://liberapay.com/assets/widgets/donate.svg)](https://liberapay.com/black-sheep-dev/donate)