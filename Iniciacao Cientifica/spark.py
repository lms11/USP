#!/usr/bin/python
import sys

from pyspark import SparkContext

if __name__ == "__main__":
	sc = SparkContext(appName="ICWordCounter")
	hadoopConf = sc.hadoopConfiguration
	hadoopConf.set("fs.s3.impl", "com.amazon.ws.emr.hadoop.fs.EmrFileSystem")
	hadoopConf.set("fs.s3.awsAccessKeyId", "AKIAI5HDGNZRWO4WGKZA")
	hadoopConf.set("fs.s3.awsSecretAccessKey", "3SfQ9LJylbdF//UVYDsCi0thzHrWDQo1iIqXWFh1")

	text_file = sc.textFile("s3://iniciacao-cientifica/medium_sample.txt")
	counts = text_file.flatMap(lambda line: line.split(" ")) \
					.map(lambda word: 1) \
					.reduce(lambda a, b: a + b)

	sc.parallelize([ counts ], 1).saveAsTextFile("s3://iniciacao-cientifica/spark-medium-output.txt")

	sc.stop()
