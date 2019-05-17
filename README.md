![GitHub license](https://img.shields.io/github/license/torresflo/QGooglePhotos.svg)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](http://makeapullrequest.com)
![GitHub contributors](https://img.shields.io/github/contributors/torresflo/QGooglePhotos.svg)
![GitHub issues](https://img.shields.io/github/issues/torresflo/QGooglePhotos.svg)

<p align="center">
  <h1 align="center">QGooglePhotos</h3>

  <p align="center">
    A Qt/C++ application and library to access and retrieve data from Google Photos.
    <br />
    <a href="https://github.com/torresflo/QGooglePhotos/issues">Report a bug or request a feature</a>
  </p>
</p>

## Table of Contents

* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Library](#library)
* [Contributing](#contributing)
* [License](#license)

## Getting Started

### Prerequisites

The project is compiled with <a href="https://doc.qt.io/qt-5/index.html">Qt 5.11.2</a>. The Qt add-on <a href="https://doc.qt.io/qt-5/qtnetworkauth-index.html">Qt Network Authorization</a> must be installed to build the project.

You need to register a new project in the <a href="https://console.developers.google.com/">Google Developpers Console</a> as no one is provided. This step is necessary because you have to request the client credentials to identify your application. 

You can follow <a href="https://blog.qt.io/blog/2017/01/25/connecting-qt-application-google-services-using-oauth-2-0/">this tutorial</a>. Note: With Qt, the redirect URI must now be `http://localhost:8080/`.

### Installation

Follow the instructions above then clone the repo (`git clone https:://github.com/torresflo/QGooglePhotos.git`) and build the project.

To run, the project is expecting the file `clientid.json` that contains the credentials of your Google Application at the root of the execuable of the project. Note: With Qt Creator, it should be placed in the build directory.

The file sould be similar to this one:
```json
{
    "web":
    {
        "client_id":"YOU_CLIENT_ID_HERE",
        "project_id":"YOUR_APPLICATION_NAME_HERE",
        "auth_uri":"https://accounts.google.com/o/oauth2/auth",
        "token_uri":"https://oauth2.googleapis.com/token",
        "client_secret":"YOUR_CLIENT_SECRET_HERE",
        "redirect_uris":["http://localhost:8080/"]
    }
}
```

## Usage

The project is divided in two parts, a library (folder `GooglePhotos`) and a simple application (folders `Application`and `Widgets`).

When starting the application, in the main menu, go to `Settings > Connection...`. It will open your browser and ask you the authorization to access your Google Photos Library. Note: the request will be done with your credentials.

### Library

The library is using the <a href="https://developers.google.com/photos/library/guides/overview">Google Photos RESTful API</a>.

The main classes of the library are:
- LibrarySettings that represents the credentials.
- QLibraryClient that represents the Google Photos library. It is used for the connection and to retrieve the albums.
- QAlbum that represents an album in Google Photos. It is used to retrieve the media items.
- QPhotoItem that represents a photo.
- QVideoItem taht represents a video (not functionnal yet).

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the GNU General Public License v3.0. See `LICENSE` for more information.
