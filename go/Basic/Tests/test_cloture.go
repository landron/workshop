/*
 */
package main

import (
	// "errors"
	"fmt"
)

type Account struct {
	login func() error
}

func (a *Account) LoginAs(login, password string) error {
	a.login = func() (err error) {
		// err = fmt.Errorf("Not implemented yet")
		fmt.Printf("Login as %v\n", login)
		return
	}
	return a.login()
}

func (a Account) Login() error {
	if a.login == nil {
		return fmt.Errorf("LoginAs() not called yet")
	}

	return a.login()
}

func (a *Account) Disconnect() {
	a.login = nil
}

func main() {
	someone := Account{}

	login := func(login, password string) (err error) {
		err = someone.LoginAs(login, password)
		if err != nil {
			fmt.Printf("LoginAs failed: %v\n", err)
			return
		}
		err = someone.Login()
		if err != nil {
			fmt.Printf("Login failed: %v\n", err)
		}
		return
	}
	login("mylogin@bigcompany.de", "mysecret123")
	someone.Disconnect()
	err := someone.Login()
	if err != nil {
		fmt.Printf("Login failed: %v\n", err)
	}
	login("anotherlogin@bigcompany.es", "mysamesecret123")
	err = someone.Login()
	if err != nil {
		fmt.Printf("Login failed: %v\n", err)
	}
}
