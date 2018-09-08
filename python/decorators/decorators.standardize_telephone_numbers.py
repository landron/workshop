#!/usr/bin/env python3
# coding=utf-8
'''
Python decorators

https://www.hackerrank.com/challenges/standardize-mobile-number-using-decorators/problem
http://simeonfranklin.com/blog/2012/jul/1/python-decorators-in-12-steps/
'''


def wrapper(function_original):
    '''
        decorated function
    '''
    def fun(telephon_numbers):
        l_standardized = []
        for i in telephon_numbers:
            std = None
            assert len(i) >= 10
            if len(i) == 10:
                std = "+91" + i
            elif len(i) == 11:
                assert i[0] == '0'
                std = "+91" + i[1:]
            elif len(i) == 12:
                assert i[0] == '9' and i[1] == '1'
                std = "+" + i
            if not std:
                std = i
            std = std[:3]+' '+std[3:8]+' '+std[8:]
            l_standardized.append(std)
        l_standardized.sort()
        # print(telephon_numbers, l_standardized)
        return function_original(l_standardized)

    return fun


@wrapper
def sort_phone(telephon_numbers):
    '''
        original version of our function
    '''
    # print("in original sort_phone")
    print(*sorted(telephon_numbers), sep='\n')


def tests():
    '''
        tests for the current problem
    '''
    print("First list")
    sort_phone(["07895462130", "919875641230", "9195969878"])
    print("\nSecond list")
    sort_phone(["09191919191", "9100256236", "+919593621456"])


if __name__ == "__main__":
    tests()
