import axios from 'axios';

const TOKEN_KEY = 'user';

class AuthService {
  register(signUpRequest) {
    return axios.post("/api/register", signUpRequest);
  }

  confirm(jwtToken) {
    return axios.post(`/api/register/confirm/${jwtToken}`);
  }

  login(loginRequest) {
    return axios.post("/api/signin", loginRequest)
      .then(response => {
        if (response.data.jwtToken) {
          const user = {
            username: loginRequest.username,
            jwtToken: response.data.jwtToken
          }
          localStorage.setItem(TOKEN_KEY, JSON.stringify(user));
        }

        return response.data;
      });
  }

  logout() {
    localStorage.removeItem(TOKEN_KEY);
    return axios.post("/api/signout");
  }

  getJwtToken() {
    const userString = localStorage.getItem(TOKEN_KEY);
    const user = JSON.parse(userString);

    const jwtToken = user.jwtToken;

    return jwtToken;
  }

  setJwtToken(token) {
    const userString = localStorage.getItem(TOKEN_KEY);
    const user = JSON.parse(userString);
    user.jwtToken = token;

    localStorage.setItem(TOKEN_KEY, JSON.stringify(user));
  }

  getCurrentUser() {
    const userString = localStorage.getItem(TOKEN_KEY);
    const user = JSON.parse(userString);

    if (user) {
      const payload = JSON.parse(atob(user.jwtToken.split('.')[1]));
      return payload.sub;
    }

    return null;
  }
}

const authService = new AuthService();

export default authService;
