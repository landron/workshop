#!/usr/bin/env python3
# coding=utf-8
'''
    Python learn
        how to force a certain locale ignoring the OS?
        * not possible, apparently
            (even if en_US should have everywhere some equivalent)
        * not only this, but also dangerous - as it is global

    https://www.hackerrank.com/challenges/python-time-delta

    tag_learn
    tag_learn_python: locale, context manager, global
    tag_class_python: "subclassing with context managers"

    flake8, pylint
'''
import datetime
import locale


class PrettyFileWriter:
    '''
        "A Gentle Introduction to Context Managers:
            The Pythonic Way of Managing Resources"
        https://alysivji.github.io/managing-resources-with-context-managers-pythonic.html

        "subclassing file objects"
        https://stackoverflow.com/questions/16085292
    '''
    def __init__(self, fileName):
        self.file = open(fileName, 'w')

    def __enter__(self):
        # return self.file
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.file.close()

    def writenl(self, line):
        '''
            normal "write" function, but also add a new line
                (the reason of this "subclassing", PrettyFileWriter)
        '''
        self.file.write(line)
        self.file.write('\n')


def time_delta(time1, time2):
    '''
        calculate the difference between the two given times
    '''
    dt1 = datetime.datetime.strptime(time1, "%a %d %b %Y %H:%M:%S %z")
    dt2 = datetime.datetime.strptime(time2, "%a %d %b %Y %H:%M:%S %z")
    timedelta = dt1 - dt2
    return str(abs(int(timedelta.total_seconds())))


def parse_with(input_func, output_func):
    '''
        parse the HackerRank input
    '''
    no_tests = int(input_func().strip())
    for _ in range(no_tests):
        diff = time_delta(input_func().strip(), input_func().strip())
        output_func(diff)


def parse_big_test():
    '''
        parse some big file HackerRank input
    '''
    fptr = open('input01.txt', 'r')
    with PrettyFileWriter('output01-mine.txt') as fptr_w:
        parse_with(fptr.readline, fptr_w.writenl)


def tests():
    '''
        tests for the current problem

        pass -O to ignore assertions and gain some time:
            py -3 -O ./prob.py
    '''
    locale.setlocale(locale.LC_TIME, "")
    loc = locale.getlocale(locale.LC_TIME)
    # Windows 7: ('English_United States', '1252')
    print(loc)
    # No:   locale.setlocale(locale.LC_TIME, "en-US")
    # No:   locale.setlocale(locale.LC_TIME, "de_DE")
    # Win7: locale.setlocale(locale.LC_TIME, "English_United States")

    # print(len(locale.locale_alias), locale.locale_alias)

    # datetime_object = datetime.datetime.strptime(
    #     "Sun 10 May 2015 13:54:36 -0700", "%c %z")
    datetime_object = datetime.datetime.strptime(
        "Sun 10 May 2015 13:54:36 -0700", "%a %d %b %Y %H:%M:%S %z")
    # datetime_object = datetime.datetime.strptime(
    #     "10 May 2015 13:54:36 -0700", "%d %b %Y %H:%M:%S %z")
    print(datetime_object)


def main():
    '''main'''
    tests()
    # parse_big_test()


if __name__ == "__main__":
    main()
