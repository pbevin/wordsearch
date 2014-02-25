# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'wordsearch/version'

Gem::Specification.new do |spec|
  spec.name          = "wordsearch"
  spec.version       = Wordsearch::VERSION
  spec.authors       = ["Pete Bevin"]
  spec.email         = ["pete@petebevin.com"]
  spec.summary       = %q{Search dictionary for anagrams, missing letters, etc.}
  # spec.description   = %q{TODO: Write a longer description. Optional.}
  spec.homepage      = ""
  spec.license       = "MIT"
  spec.extensions    = ["ext/wordsearch/extconf.rb"]

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib", "ext"]

  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "rake"
end
