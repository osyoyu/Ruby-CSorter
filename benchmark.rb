# coding: UTF-8
require 'benchmark'
require 'sorter'

def create_array(n)
  prng = Random.new
  array = Array.new
  n.times do
    array.push(prng.rand(n+1).to_i + 1)
  end
  return array
end

def print_array(array)
  array.each do |n|
    print "#{n}, "
  end
  print "\n"
end

def sorted?(array)
  return true if array.length <= 1
  1.upto(array.length - 1) do |i|
    return false if array[i - 1] > array[i]
  end
  return true
end

def ruby_bogosort(array)
  count = 0

  while !sorted?(array)
    # print_array(array)
    array.shuffle!
    count += 1
  end

  puts "Ruby: done in #{count} times"
  return array
end

def c_bogosort(array)
  Sorter.bogosort(array)
end

bogo = 1
loop do
  3.times do
    array = create_array(bogo)
    puts "#{array.length}-bogosort: #{print_array(array)}"

    starttime = Time.now
    c_bogosort(array.clone)
    puts "C:    #{Time.now - starttime}s"
  end
  bogo = bogo + 1
  puts "#############"
end
