require "wordsearch/version"
require "wordsearch/wordsearch"

class Wordsearch
  def initialize(dictionary=ENV["ANAGRAM_DICT"])
    @dict = dictionary
  end

  def anagrams(pattern, &block)
    an(pattern, &block)
  end

  def find_words(pattern, &block)
    fw(pattern, &block)
  end

  def solve_cryptogram(pattern, &block)
    cr(pattern, &block)
  end
end
