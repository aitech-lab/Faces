{ get  } = require "request"
{ exec } = require "child_process"

minage = 18
maxage = 40
for page in [1..100]
  console.log page
  url = "https://www.backstage.com/talent/async/search/?max_age__gte=#{minage}&min_age__lte=#{maxage}&page=#{page}"
  await get url, defer(err, res, data)
  try
    json = JSON.parse data
    errs   = []
    stderr = []
    stdout = []
    await for item, i in json?.items
      { gender, django_id, media_objs } = item
      { media_url } = media_objs[0]
      file = "#{gender}_#{django_id}"
      exec "convert #{media_url} -resize 960x960 ../data/#{file}.jpg", defer(errs[i], stderr[i], stdout[i])
  catch err
    console.error err